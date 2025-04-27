import os

def find_large_files(directory, size_in_mb=1):
    size_limit = size_in_mb * 1024 * 1024  # convert MB to bytes

    print(f"Searching for files larger than {size_in_mb} MB in '{directory}'...\n")

    for root, _, files in os.walk(directory):
        for file in files:
            file_path = os.path.join(root, file)
            try:
                file_size = os.path.getsize(file_path)
                if file_size > size_limit:
                    size_in_mb = file_size / (1024 * 1024)
                    print(f"{file_path} --> {size_in_mb:.2f} MB")
            except FileNotFoundError:
                continue

if __name__ == "__main__":
    # Automatically get the directory where this script is located
    script_directory = os.path.dirname(os.path.abspath(__file__))

    find_large_files(script_directory)
