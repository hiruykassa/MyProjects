def add_time(start, duration, day_of_week=None):
    # Split the start time into components
    time, period = start.split()
    hour, minute = map(int, time.split(':'))
    duration_hour, duration_minute = map(int, duration.split(':'))
    
    # Convert start hour to 24-hour format for easier calculation
    if period == "PM":
        hour += 12
    if hour == 12 and period == "AM":  # Midnight case
        hour = 0

    # Add the duration to the current time
    total_minutes = minute + duration_minute
    extra_hour = total_minutes // 60
    final_minute = total_minutes % 60

    total_hours = hour + duration_hour + extra_hour
    final_hour_24 = total_hours % 24
    days_later = total_hours // 24

    # Convert back to 12-hour format
    final_period = "AM" if final_hour_24 < 12 else "PM"
    final_hour = final_hour_24 % 12
    if final_hour == 0:
        final_hour = 12

    # Calculate the resulting day of the week (if provided)
    if day_of_week:
        days = ["Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"]
        start_day_index = days.index(day_of_week.capitalize())
        end_day_index = (start_day_index + days_later) % 7
        end_day = days[end_day_index]
        day_output = f", {end_day}"
    else:
        day_output = ""

    # Format the number of days later
    if days_later == 1:
        day_later_output = " (next day)"
    elif days_later > 1:
        day_later_output = f" ({days_later} days later)"
    else:
        day_later_output = ""

    # Construct the final time string
    new_time = f"{final_hour}:{str(final_minute).zfill(2)} {final_period}{day_output}{day_later_output}"
    return new_time

print(add_time('10:10 AM', '200:45', 'Monday'))