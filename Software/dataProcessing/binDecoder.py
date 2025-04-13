import struct
import csv

# Define the format strings for unpacking the binary data
lsm_format = "fff"        # Format for lsmDataStruc (3x float)
mpu_format = "fffffff"    # Format for mpuDataStruc (7x float)
bmp_format = "ff"    # Format for mpuDataStruc (2x float)

#padding_format = "L" #(1xpadding)

allStrucFormat = lsm_format + mpu_format + bmp_format


lsm_header = ['lsmMagX', 'lsmMagY', 'lsmMagZ']
mpu_header = ['mpuAccelX', 'mpuAccelY', 'mpuAccelZ', 'mpuGyroX', 'mpuGyroY', 'mpuGyroZ', 'mpuTemp']
bmp_header = ['pressure', 'temperature']
padding_header = [
    'padding'
]

allStrucHeader = lsm_header + mpu_header + bmp_header

# Function to check if all elements between n and m in a list are zero and replace them with empty strings
def replace_zeros_with_empty(arr, n, m):
    if all(x == 0 for x in arr[n:m+1]):
        for i in range(n, m+1):
            arr[i] = ''
    return arr

# Function to replace zeros with empty strings for specific headers
def replace_zeros_in_sections(data, headers, sections):
    for section in sections:
        start_index = headers.index(section[0])
        end_index = headers.index(section[-1])
        data = replace_zeros_with_empty(data, start_index, end_index)
    return data

# Open the binary file for reading
try:
    with open('IMUDATA.BIN', 'rb') as f:
        data = f.read()

    # Define the output CSV file name
    csv_file = 'output.csv'

    # Open the CSV file for writing
    with open(csv_file, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)

        # Write the header row
        writer.writerow(allStrucHeader)

        # Unpack the binary data and write to CSV row by row
        record_size = struct.calcsize(allStrucFormat)
        for i in range(0, len(data), record_size):
            unpacked_data = list(struct.unpack(allStrucFormat, data[i:i + record_size]))

            # Define sections to check for zeros
            sections = [lsm_header, mpu_header, bmp_header]
            
            # Replace zeros with empty strings in specified sections
            unpacked_data = replace_zeros_in_sections(unpacked_data, allStrucHeader, sections)
            
            # Convert data to strings and write to CSV
            writer.writerow([str(item) for item in unpacked_data])

    print(f"CSV file '{csv_file}' has been created successfully.")

except FileNotFoundError:
    print("The binary file 'IMUDATA.BIN' was not found.")
except struct.error as e:
    print(f"Error unpacking binary data: {e}")
except Exception as e:
    print(f"An unexpected error occurred: {e}")
