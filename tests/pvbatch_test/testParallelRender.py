from paraview.simple import *

n_procs = 8

CreateRenderView()
Sphere(ThetaResolution=100, PhiResolution=100)
ProcessIdScalars()
Show()

lt = CreateLookupTable(RGBPoints=[0.0, 0, 0, 1, n_procs-1, 1, 0, 0], ColorSpace = "HSV")
SetDisplayProperties(ColorAttributeType=0, ColorArrayName="ProcessId", LookupTable=lt)
Render()

WriteImage("coloredSphere.png")
