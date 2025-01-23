def arithmetic_arranger(problems, show_answers=False):
    if len(problems) > 5:
        return "Error: Too many problems."

    first_line = []
    second_line = []
    dashes = []
    answers = []

    for problem in problems:
        parts = problem.split()

        
        if len(parts) != 3:
            return "Error: Each problem must consist of two operands and an operator."

        left_operand, operator, right_operand = parts

        if operator not in ["+", "-"]:
            return "Error: Operator must be '+' or '-'."
        if not(left_operand.isdigit() and right_operand.isdigit()):
            return "Error: Numbers must only contain digits."
        if len(left_operand) > 4 or len(right_operand) > 4:
            return "Error: Numbers cannot be more than four digits."

        if operator == "+":
            result = int(left_operand) + int(right_operand)
        else:
            result = int(left_operand) - int(right_operand)

        width = max(len(left_operand), len(right_operand)) + 2 

        
        first_line.append(left_operand.rjust(width))
        second_line.append(operator + right_operand.rjust(width - 1))
        dashes.append("-" * width)
        answers.append(str(result).rjust(width))

    
    arranged_first_line = "    ".join(first_line)
    arranged_second_line = "    ".join(second_line)
    arranged_dashes = "    ".join(dashes)
    arranged_answers = "    ".join(answers)

    
    if show_answers:
        return f"{arranged_first_line}\n{arranged_second_line}\n{arranged_dashes}\n{arranged_answers}"
    else:
        return f"{arranged_first_line}\n{arranged_second_line}\n{arranged_dashes}"

print(f'\n{arithmetic_arranger(["32 + 698", "3801 - 2", "45 + 43", "123 + 49"])}')