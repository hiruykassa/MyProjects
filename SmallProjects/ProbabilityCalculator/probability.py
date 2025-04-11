import random

class Hat:
    def __init__(self, **balls):
        self.contents = []
        for color, count in balls.items():
            self.contents.extend([color] * count)

    def draw(self, num_balls):
        drawn_balls = random.sample(self.contents, min(num_balls, len(self.contents)))
        for ball in drawn_balls:
            self.contents.remove(ball)
        return drawn_balls


def experiment(hat, expected_balls, num_balls_drawn, num_experiments):
    success_count = 0

    for _ in range(num_experiments):
        # Make a copy of the hat for each experiment to avoid modifying the original
        hat_copy = Hat(**{color: hat.contents.count(color) for color in set(hat.contents)})
        drawn_balls = hat_copy.draw(num_balls_drawn)
        
        # Count the number of each color in the drawn balls
        drawn_ball_counts = {color: drawn_balls.count(color) for color in set(drawn_balls)}

        # Check if the drawn balls meet or exceed the expected number of each color
        if all(drawn_ball_counts.get(color, 0) >= expected_balls.get(color, 0) for color in expected_balls):
            success_count += 1

    return success_count / num_experiments


# Example usage:
hat = Hat(blue=5, red=4, green=2)
probability = experiment(hat=hat,
                         expected_balls={'red': 1, 'green': 2},
                         num_balls_drawn=4,
                         num_experiments=2000)

print(f"Estimated Probability: {probability}")
