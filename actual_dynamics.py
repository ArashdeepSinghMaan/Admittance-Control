# Given values
m = 1.0    # mass in kg
b = 2.0    # damping coefficient in N.s/m
k = 0.1    # stiffness coefficient in N/m
time_interval = 1.0  # time in seconds

# Position from virtual dynamics
y_desired = 1.4  # meters

# Assume initial position and velocity are zero
y_initial = 0.0
v_initial = 0.0

# Calculate velocity (approximate average)
velocity = (y_desired - y_initial) / time_interval  # m/s

# Calculate acceleration (approximate average)
acceleration = (velocity - v_initial) / time_interval  # m/s²

# Calculate control input (force/torque)
u = m * acceleration + b * velocity + k * y_desired

# Print results
print(f"Velocity after {time_interval} sec: {velocity:.4f} m/s")
print(f"Acceleration after {time_interval} sec: {acceleration:.4f} m/s²")
print(f"Control input (force/torque) needed: {u:.4f} N")
