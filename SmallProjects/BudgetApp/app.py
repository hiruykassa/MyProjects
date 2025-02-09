class Category:
    def __init__(self, name):
        self.name = name  
        self.ledger = []

    def deposit(self, amount, description=''):
        self.ledger.append({'amount': amount, 'description': description})

    def withdraw(self, amount, description=''):
        if self.check_funds(amount):  
            self.ledger.append({'amount': -amount, 'description': description})
            return True
        return False

    def get_balance(self):
        return sum(entry['amount'] for entry in self.ledger)

    def transfer(self, amount, category):
        if self.check_funds(amount):  
            self.withdraw(amount, f"Transfer to {category.name}")
            category.deposit(amount, f"Transfer from {self.name}")
            return True
        return False

    def check_funds(self, amount):  
        return amount <= self.get_balance()  

    def __str__(self):
        title = f"{self.name:*^30}\n"
        items = ""
        for entry in self.ledger:
            items += f"{entry['description'][:23]:23}{entry['amount']:>7.2f}\n"
        total = f"Total: {self.get_balance():.2f}"
        return title + items + total


def create_spend_chart(categories):
    # Calculate total spent (as a positive value) for all categories
    total_spent = sum(
        -entry['amount'] for cat in categories for entry in cat.ledger if entry['amount'] < 0
    )

    # Calculate total spent per category (as positive values)
    category_spent = {
        cat.name: sum(-entry['amount'] for entry in cat.ledger if entry['amount'] < 0)
        for cat in categories
    }

    # Calculate percentage spent per category, rounded down to the nearest 10
    category_percentages = {
        name: int(category_spent[name] / total_spent * 100) // 10 * 10 if total_spent > 0 else 0
        for name in category_spent
    }

    chart = "Percentage spent by category\n"

    # Build the chart from 100 down to 0
    for i in range(100, -1, -10):
        chart += f"{i:>3}| "
        for cat in categories:
            if category_percentages[cat.name] >= i:
                chart += "o  "
            else:
                chart += "   "
        chart += "\n"

    # Add the horizontal line. For each category we need 3 characters, plus one extra dash.
    chart += "    " + "-" * (len(categories) * 3 + 1) + "\n"

    # Prepare the category names to be printed vertically.
    max_length = max(len(cat.name) for cat in categories)
    names_padded = [cat.name.ljust(max_length) for cat in categories]

    # Build each line of vertical names so that each line has the same length.
    for i in range(max_length):
        line = "     "
        for name in names_padded:
            line += name[i] + "  "
        if i < max_length - 1:
            chart += line + "\n"
        else:
            chart += line  # no newline at the end

    return chart
