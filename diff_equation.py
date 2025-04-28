import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import solve_ivp

# Define the external force as a function of time
def force(t):
    if t <= 1.0:
        return 3.5
    else:
        return 0.0

# Define the system of first-order ODEs
# Let y[0] = position, y[1] = velocity
def system(t, y):
    dydt = [0, 0]
    dydt[0] = y[1]                          # dy/dt = velocity
    dydt[1] = (-2.0*y[1] - 0.8*y[0] + force(t))/0.1    # d²y/dt² from the equation
    return dydt

# Initial conditions: y(0) = 0 (position), y'(0) = 0 (velocity)
y0 = [0, 0]

# Time span for simulation
t_span = (0, 10)  # from t=0 to t=10 seconds
t_eval = np.linspace(t_span[0], t_span[1], 1000)  # points where solution is computed

# Solve the ODE
solution = solve_ivp(system, t_span, y0, t_eval=t_eval)

# Plot the results
plt.figure(figsize=(10, 6))
plt.plot(solution.t, solution.y[0], label='Position y(t)')
plt.plot(solution.t, solution.y[1], label='Velocity dy/dt')
plt.axvline(1, color='red', linestyle='--', label='Force turned off at t=1s')
plt.title('Second-order System Response to Temporary Force')
plt.xlabel('Time [s]')
plt.ylabel('Response')
plt.legend()
plt.grid(True)
plt.show()
