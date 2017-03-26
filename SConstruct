import glob
import os
import sys

def checkDirEnding(fdir):
    return fdir if fdir[-1] == os.sep else fdir+os.sep

def getSrcFromFolder(srcDirs, srcPattern, trgtDir):
    #print("Extract files from " , srcDirs)
    res=[]
    trgtDir = checkDirEnding(trgtDir)
    for srcF in srcDirs:
        srcF = checkDirEnding(srcF)
        print("Process %s folder" % srcF)
        for f in glob.glob(srcF+srcPattern):
            res.append(trgtDir+f)
    return tuple(res)

def RegisterSrcFolderInEnv(srcDirs, env, trgtDir):
    for srcF in srcDirs:
        print("Register folder %s" % (srcF))
        srcF = checkDirEnding(srcF)
        env.VariantDir(trgtDir+srcF, srcF, duplicate=0)

testComLib = 'ctest'
cutLib  =   'cut'
debug = False

if ARGUMENTS.get('debug', '0') == '1':
    print "*** Debug build..."
    binFolder = 'bin/Debug/'
    debug = True
else:
    print "*** Release build..."
    binFolder = 'bin/Release/'

target = ARGUMENTS.get('target', '')
testComFiles =()
testCutFiles = ()
cutFolders =()
genTestFolders = ('./tests/',)
incPath  = ('inc/',)

if  target == 'test_common':
    print("Create common tests.")
    cutFolders += ('./src/',)
    testCutFolders = ('./tests/',)
elif target == 'test_display':
    print("Create display tests.")
    cutFolders += ('./src/','./display/src/')
    testCutFolders = ('./display/tests/',)
    incPath+=('display/inc/',)
else:
    print("Build everything")

testCutFiles += getSrcFromFolder(testCutFolders,'*Test.cpp',binFolder)
testComFiles += getSrcFromFolder(genTestFolders,'AllTests.cpp',binFolder)
cutFiles = getSrcFromFolder(cutFolders,'*.cpp',binFolder)
cutFiles += getSrcFromFolder(cutFolders,'*.c',binFolder)
print(testComFiles)
print(testCutFiles)
print(cutFiles)
linkLibs = ('CppUTest','CppUTestExt')
libPath  = binFolder
ccDebFlags = '-g'
ccFlags  = '-Wall ' + "" if not debug else " %s" % ccDebFlags
cflags = " -std=c11"
cxxflags=" -std=c++11"
env = Environment(variant_dir=binFolder,
                  LIBPATH=binFolder,
                  LIBS=(cutLib,testComLib)+linkLibs,
                  CPPPATH=incPath, CCFLAGS=ccFlags,
                  CFLAGS=cflags, CXXFLAGS=cxxflags)

RegisterSrcFolderInEnv(cutFolders, env, binFolder)
env.Library(target=binFolder+cutLib, source= cutFiles)

RegisterSrcFolderInEnv(testCutFolders, env, binFolder)

RegisterSrcFolderInEnv(genTestFolders, env, binFolder)
env.Library(target=binFolder+testComLib, source= testComFiles)

if target == '':
    print("Not supported")
    sys.exit()
    f='common/Test.cpp'
    of=of=f.split(os.sep)[1].split('.')[0]
    env.Program(binFolder+of, (binFolder+f,))
    for f in glob.glob('*/tests/*Test.cpp'):
        of=f.split(os.sep)[1].split('.')[0]
        env.Program(binFolder+of, (binFolder+f,))
else:
     for f in testCutFiles:
        of=f.split(os.sep)[-1].split('.')[0]
        print(f, of)
        env.Program(binFolder+of, (f,))
   
