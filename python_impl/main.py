import pygame
import math

# --- CONFIGURATION ---
WIDTH, HEIGHT = 800, 600
L1 = 200  # Length of shoulder-to-elbow
L2 = 150  # Length of elbow-to-hand
ORIGIN = (WIDTH // 2, HEIGHT // 2) # Base of the robot (center of screen)

# Colors
BLACK = (30, 30, 30)
WHITE = (255, 255, 255)
RED = (200, 50, 50)
GREEN = (50, 200, 50)

class RobotArm:
    def __init__(self):
        self.theta1 = 0.0 # Shoulder angle
        self.theta2 = 0.0 # Elbow angle

    def update(self, target_x, target_y):
        """
        Calculates the joint angles (Inverse Kinematics) 
        to reach the target (x, y).
        """
        # Coordinate Shift: Make the base (0,0) relative to the arm, not the screen
        dx = target_x - ORIGIN[0]
        dy = target_y - ORIGIN[1]

        # Distance Calculation (Hypotenuse)
        dist = math.sqrt(dx**2 + dy**2)

        # SAFETY CLAMP: If target is further than arm can reach, 
        # scale the vector back so the arm doesn't "break"
        max_reach = L1 + L2
        if dist > max_reach:
            scale = max_reach / dist
            dx *= scale
            dy *= scale
            dist = max_reach # Cap the distance for the math below

        # THE MATH: Law of Cosines

        
        try:
            cos_theta2 = (dx**2 + dy**2 - L1**2 - L2**2) / (2 * L1 * L2)
            
            # Clamp value to [-1, 1] to handle floating point errors
            cos_theta2 = max(-1.0, min(1.0, cos_theta2))
            
            self.theta2 = math.acos(cos_theta2) # This gives the elbow angle inside the triangle

            # Calculate Shoulder Angle (theta1)

            k1 = L1 + L2 * math.cos(self.theta2)
            k2 = L2 * math.sin(self.theta2)
            
            self.theta1 = math.atan2(dy, dx) - math.atan2(k2, k1)

        except ValueError:
            pass # Math error (shouldn't happen with the clamp above)

    def draw(self, surface):
        # Forward Kinematics: Calculate (x,y) of joints to draw lines
        
        # Joint 1 (Shoulder/Base)
        x0, y0 = ORIGIN
        
        # Joint 2 (Elbow)
        x1 = x0 + L1 * math.cos(self.theta1)
        y1 = y0 + L1 * math.sin(self.theta1)
        
        # End Effector (Hand)
        # Angle is sum of theta1 + theta2
        x2 = x1 + L2 * math.cos(self.theta1 + self.theta2)
        y2 = y1 + L2 * math.sin(self.theta1 + self.theta2)

        # Draw Links
        pygame.draw.line(surface, WHITE, (x0, y0), (x1, y1), 5)
        pygame.draw.line(surface, WHITE, (x1, y1), (x2, y2), 5)
        
        # Draw Joints
        pygame.draw.circle(surface, GREEN, (int(x0), int(y0)), 8)
        pygame.draw.circle(surface, RED, (int(x1), int(y1)), 6)
        pygame.draw.circle(surface, RED, (int(x2), int(y2)), 4)

# --- MAIN LOOP ---
pygame.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Robot Arm - Python Prototype")
clock = pygame.time.Clock()

arm = RobotArm()

running = True
while running:
    screen.fill(BLACK)
    
    # Event Handling
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Logic
    mouse_x, mouse_y = pygame.mouse.get_pos()
    arm.update(mouse_x, mouse_y)
    
    # Render
    arm.draw(screen)
    
    pygame.display.flip() 
    
    clock.tick(30) 

pygame.quit()