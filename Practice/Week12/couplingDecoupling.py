# Coupled Functions
def calculate_total_price(quantity, unit_price, tax_rate):
    subtotal = quantity * unit_price
    total_price = subtotal + (subtotal * tax_rate)
    return total_price


# violates SRP (has 2 reasons to change -> calculation change, print change)
def print_invoice(quantity, unit_price, tax_rate):
    total_price = calculate_total_price(quantity, unit_price, tax_rate)
    print(
        f"Invoice\nQuantity: {quantity}\nUnit Price: ${unit_price}\nTotal Price: ${total_price}", end="\n\n")


print_invoice(5, 10, 0.1)

#
#
# Decoupled (follows SRP) - change in calculation logic won't change printing logic


def print_invoice(quantity, unit_price, total_price):
    print(
        f"Invoice\nQuantity: {quantity}\nUnit Price: ${unit_price}\nTotal Price: ${total_price}")


quantity = 5
unit_price = 10
total_price = calculate_total_price(quantity, unit_price, 0.1)
print_invoice(quantity, unit_price, total_price)
