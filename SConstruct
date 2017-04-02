import glob
import os
import sys
import re

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

def modify_chip_definitions(files=None, define_name='PERIPH_BASE'):
    keyPtr1 = re.compile(r'#if[\s]+!defined\((.*)\)')
    keyPtr2 = re.compile(r'#define[\s]+(%s)[\s]+([0-9xU]+)[\s]+(.*)' %define_name) 
    if files is None:
        files = ('pin','test','stm','f4','inc','stm32f4[0-9]*')
    for f in glob.glob(os.sep.join(files)):
        print("Check file %s " % f)
        with open(f, 'rw') as fd:
            res = []
            for line in fd.readlines():
                line = line.strip()
                mtch = keyPtr1.match(line)
                if mtch is not None:
                    print("file %s is already modified" % f)
                    res = None                    
                    break
                mtch = keyPtr2.match(line)
                if mtch is not None:
                    res.append("#if !defined(%s)" % define_name)
                res.append(line)
                if mtch is not None:
                    res.append("#endif")
        if res is not None:
            print("Rewrite %s" % f)
            with open(f, 'w') as fd:
                fd.write(os.linesep.join(res))               
modify_chip_definitions()
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
    print("Create pin mock tests.")
    cutFolders += ('./pin/src/', )
    testCutFolders = ('./pin/test/',)
    drvFolder = ('./pin/drv/',)
    drvFiles += getSrcFromFolder(drvFolder,'pin_mock.cpp',binFolder)
    drvFiles += getSrcFromFolder(drvFolder,'pin_stm32f4.cpp',binFolder)
    incPath+=('pin/inc/',)
    incPath+=('pin/test/',)
    incPath+=('pin/test/stm/',)
    incPath+=('pin/test/stm/f4/',)
    incPath+=('pin/test/stm/f4/inc/',)
    incPath+=('pin/drv/',)
    incPath+=('port/inc/',)
    linkLibs +=(drvLib,)
    ccFlags ="-DSTM32F407xx -DSTM32 "
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
ccFlags  += '-Wall -DUNIT_TEST ' + ("" if not debug else " %s" % ccDebFlags)
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
    env.Program(binFolder+of, (f,))
   
