def line_from_points(x1, y1, x2, y2):
    """
    Given two points (x1, y1) and (x2, y2),
    returns slope (m) and intercept (b) of the line y = mx + b.
    """
    if x2 == x1:
        raise ValueError("x1 and x2 cannot be the same (vertical line)")

    m = (y2 - y1) / (x2 - x1)
    b = y1 - m * x1
    return m, b

def format_line(m, b):
    """
    Returns a string representing the line equation in y = mx + b form.
    """
    sign = '+' if b >= 0 else '-'
    return f"y = {m:.5f}x {sign} {abs(b):.5f}"

# Example usage
x1, y1 = 5.0, 0.0
x2, y2 = 10.0, 1.0

m, b = line_from_points(x1, y1, x2, y2)
print(f"Slope: {m}")
print(f"Line: {format_line(m, b)}")