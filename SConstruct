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
drvLib  =   'drv'
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
genTestFolders = ('./test/',)
incPath  = ('inc/',)

drvFiles =()
drvFolder =()
linkLibs =(cutLib,testComLib)

if  target == 'test_common':
    print("Create common tests.")
    cutFolders += ('./src/',)
    testCutFolders = ('./test/',)
elif target == 'test_display':
    print("Create display tests.")
    cutFolders += ('./display/src/', )
    testCutFolders = ('./display/test/',)
    testComFiles += getSrcFromFolder(genTestFolders,'mock_common.cpp',binFolder)
    incPath+=('display/inc/',)
elif target == 'test_pin':
    print("Create pin tests.")
    cutFolders += ('./pin/src/', )
    testCutFolders = ('./pin/test/',)
    drvFolder = ('./pin/drv/',)
    drvFiles += getSrcFromFolder(drvFolder,'pin_mock.cpp',binFolder)
    incPath+=('pin/inc/',)
    incPath+=('pin/drv/',)
    incPath+=('port/inc/',)
    linkLibs +=(drvLib,)
    
else:
    print("Build everything")

linkLibs += ('CppUTest','CppUTestExt')
testCutFiles += getSrcFromFolder(testCutFolders,'*test.cpp',binFolder)
testComFiles += getSrcFromFolder(genTestFolders,'AllTests.cpp',binFolder)
cutFiles  = getSrcFromFolder(cutFolders,'*.cpp',binFolder)
cutFiles += getSrcFromFolder(cutFolders,'*.c',binFolder)
print(testComFiles)
print(testCutFiles)
print(cutFiles)
print(linkLibs)
libPath  = binFolder
ccDebFlags = '-g'
ccFlags  = '-Wall -DUNIT_TEST ' + ("" if not debug else " %s" % ccDebFlags)
cflags = " -std=c11"
cxxflags=" -std=c++11"
env = Environment(variant_dir=binFolder,
                  LIBPATH=binFolder,
                  LIBS=linkLibs,
                  CPPPATH=incPath, CCFLAGS=ccFlags,
                  CFLAGS=cflags, CXXFLAGS=cxxflags)

RegisterSrcFolderInEnv(cutFolders, env, binFolder)
env.Library(target=binFolder+cutLib, source= cutFiles)

if len(drvFiles)>0:
	print("Build driver library")
	RegisterSrcFolderInEnv(drvFolder, env, binFolder)
	env.Library(target=binFolder+drvLib, source= drvFiles)

RegisterSrcFolderInEnv(testCutFolders, env, binFolder)

RegisterSrcFolderInEnv(genTestFolders, env, binFolder)
env.Library(target=binFolder+testComLib, source= testComFiles)

for f in testCutFiles:
    of=f.split(os.sep)[-1].split('.')[0]
    of = 'unit_test'
    env.Program(binFolder+of, (f,))
   
