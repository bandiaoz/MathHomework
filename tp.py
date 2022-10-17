import os

for i in range(1, 8):
    os.system("git rm -r --cached ./OptimizationMethod/OptimizationMethod{}/*.aux".format(i))
    os.system("git rm -r --cached ./OptimizationMethod/OptimizationMethod{}/*.log".format(i))
    os.system("git rm -r --cached ./OptimizationMethod/OptimizationMethod{}/*.out".format(i))
    os.system("git rm -r --cached ./OptimizationMethod/OptimizationMethod{}/*.synctex.gz".format(i))