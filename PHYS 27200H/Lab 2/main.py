from vpython import *

#Problems 1-4 on Lab 1.pdf

#Define Constants

e = 1.6e-19
oofpez = 9e9
scalefactor = 0.5e-9/3.182e8

#Initial Values

theta = 0
phi = 0
r = 2e-9


atom1 = sphere(pos = vector(0.5e-9,0,0), radius = 1e-10, color = color.blue)
atom1.q = -e

atom2 = sphere(pos = vector(-0.5e-9,0,0), radius = 1e-10, color = color.red)
atom2.q = +e


#Calculations
while r < 10e-9:
    phi = 0
    while phi < pi:
        theta = 0
        while theta < 2*pi:

            obslocation = vector(r*cos(theta)*sin(phi),r*sin(theta)*sin(phi),r*cos(phi))

            r1 = obslocation - atom1.pos
            r2 = obslocation - atom2.pos

            magr1 = mag(r1)
            r1hat = hat(r1)

            magr2 = mag(r2)
            r2hat = hat(r2)


            E1 = r1hat*oofpez*atom1.q/magr1**2
            E2 = r2hat*oofpez*atom2.q/magr2**2

            Enet = E1 + E2

            Earrow = arrow(pos = obslocation, axis = Enet*scalefactor, color = color.orange)


            print("The observation location is", obslocation, "m")
            print("Enet: ", mag(Enet), "N/C")


            theta = theta + pi/6
        phi = phi + pi/6
    r += 1e-9




