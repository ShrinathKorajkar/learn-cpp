def calculate_and_print_circle_properties(radius):
    # Mixing higher-level print statements with lower-level calculations
    print(f"Circle Properties for Radius {radius}:")

    # Lower-level calculation for area
    area = 3.14 * radius**2
    print(f" - Area: {area}")

    # Lower-level calculation for circumference
    circumference = 2 * 3.14 * radius
    print(f" - Circumference: {circumference}")


# Single Level of Abstraction
def calculate_area(radius):
    return 3.14 * radius**2             # low level abstraction (most detailed)


def calculate_circumference(radius):
    return 2 * 3.14 * radius            # low level abstraction (most detailed)


def print_circle_properties(radius):
    # high level abstraction (less detailed)
    area = calculate_area(radius)
    circumference = calculate_circumference(radius)

    print(f"Circle Properties:")
    print(f" - Area: {area}")
    print(f" - Circumference: {circumference}")
