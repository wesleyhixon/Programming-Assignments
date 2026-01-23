from vpython import *

#Problems 1-4 on Lab 1.pdf

#Define Constants

e = 1.6e-19
oofpez = 9e9
scalefactor = 1e-7/250000

#Initial Values

obslocation = vector(0,0,0)

""" atom1 = sphere(pos = vector(-300e-9,0,0), radius = 10e-9, color = color.red)
atom1.q = 3*e

atom2 = sphere(pos = vector(100e-9,0,0), radius = 10e-9, color = color.blue)
atom2.q = -e
 """

atom1 = sphere(pos = vector(-500e-9,0,0), radius = 10e-9, color = color.red)
atom1.q = 12*e

atom2 = sphere(pos = vector(600e-9,0,0), radius = 10e-9, color = color.blue)
atom2.q = 5*e

atom3 = sphere(pos = vector(-171e-9,0,0), radius = 10e-9, color = color.green)
atom3.q = -e

Earrow = arrow(pos = obslocation, axis = vector(0,0,0), color = color.cyan)

r1 = Earrow.pos - atom1.pos
r2 = Earrow.pos - atom2.pos
r3 = Earrow.pos - atom3.pos

magr1 = mag(r1)
r1hat = hat(r1)

magr2 = mag(r2)
r2hat = hat(r2)

magr3 = mag(r3)
r3hat = hat(r3)

E1 = r1hat*oofpez*atom1.q/magr1**2
E2 = r2hat*oofpez*atom2.q/magr2**2
E3 = r3hat*oofpez*atom3.q/magr3**2

Enet = E1 + E2 + E3
Earrow.axis = scalefactor*Enet

print("The magnitude of E1:", mag(E1), "N/C")
print("The magnitude of E2:", mag(E2), "N/C")
print("The magnitude of E3:", mag(E3), "N/C")
print("The magnitude of Enet:", mag(Enet), "N/C")


