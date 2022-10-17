import os

def get_files():
    for filepath,dirnames,filenames in os.walk(r'.'):
        for filename in filenames:
            if filename.split('.')[-1] in ['aux', 'log', 'out', 'gz', 'DS_Store']:
                os.system("git rm -r --cached " + filepath + '/' + filename)

get_files()