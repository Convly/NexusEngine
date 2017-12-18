#!/usr/bin/env python3

import os
import sys
import argparse
import shutil
import datetime
import fileinput

binPath = os.path.dirname(sys.argv[0])

class bcolors:
	HEADER = '\033[95m'
	OKBLUE = '\033[94m'
	OKGREEN = '\033[92m'
	WARNING = '\033[96m'
	FAIL = '\033[91m'
	ENDC = '\033[0m'
	BOLD = '\033[1m'
	UNDERLINE = '\033[4m'
	INFORM = '\033[93m'

def setTime(payload):
	return '[' + datetime.datetime.now().strftime('%H:%M:%S') + ']: ' + payload

def adjustParams(payload, bold, underline):
	if bold: payload = bcolors.BOLD + payload
	if underline: payload = bcolors.UNDERLINE + payload
	return payload

def Warn(payload, bold=False, underline=False, end='\n'):
	payload = setTime(payload)
	payload = bcolors.WARNING + payload
	payload = adjustParams(payload, bold, underline)
	payload += bcolors.ENDC
	print(payload, end=end)

def Fail(payload, bold=False, underline=False, end='\n'):
	payload = setTime(payload)
	payload = bcolors.FAIL + payload
	payload = adjustParams(payload, bold, underline)
	payload += bcolors.ENDC
	print(payload, end=end)

def Head(payload, bold=False, underline=False, end='\n'):
	payload = setTime(payload)
	payload = bcolors.HEADER + payload
	payload = adjustParams(payload, bold, underline)
	payload += bcolors.ENDC
	print(payload, end=end)

def Inform(payload, bold=False, underline=False, end='\n'):
	payload = setTime(payload)
	payload = bcolors.INFORM + payload
	payload = adjustParams(payload, bold, underline)
	payload += bcolors.ENDC
	print(payload, end=end)

def Log(payload, bold=False, underline=False, end='\n', color='White'):
	payload = setTime(payload)    
	prefix = ''
	if color == 'Green': prefix = bcolors.OKGREEN
	elif color == 'Blue': prefix = bcolors.OKBLUE

	payload = prefix + payload
	payload = adjustParams(payload, bold, underline)
	payload += bcolors.ENDC
	print(payload, end=end)

def parse(argv):
	parser = argparse.ArgumentParser(add_help=False, description='C++ "System and Framework" generation tool for the NexusEngine')
	parser.add_argument('-help', action='help', help='Display this help')
	parser.add_argument('-r', type=str, help='is the root path of the Engine/ directory', required=True)
	parser.add_argument('-n', type=str, help='is the name of the system/framework ; written in UpperCamelCase', required=True)
	parser.add_argument('-d', help='Keyword to use when you want to remove a system and its framework', required=False, action="store_true")

	parsedArgs = parser.parse_args(argv)

	return (parsedArgs.r, parsedArgs.n, parsedArgs.d)

def deleteFiles(rootPath, fileName):
	Head("About to delete System and Framework for " + fileName)
	frameworkDirectory = rootPath + "/frameworks/" + fileName.lower()

	os.remove(rootPath + "/includes/Nexus/" + fileName.lower() + ".hpp")
	os.remove(rootPath + "/includes/Nexus/frameworks/" + fileName + "FrameworkTpl.hpp")
	os.remove(rootPath + "/src/systems/" + fileName + "System.cpp")
	shutil.rmtree(frameworkDirectory)

	Log("Done", color='Green', bold=True)

def copyFiles(rootPath, fileName):
	Head("About to create System and Framework for " + fileName)

	paths = {}
	frameworkDirectory = rootPath + "/frameworks/" + fileName.lower()
	frameworkBuildDirectory = frameworkDirectory + "/build"

	paths[binPath + "/templates/system/test.hpp.tpl"] = rootPath + "/includes/Nexus/" + fileName.lower() + ".hpp"
	paths[binPath + "/templates/system/TestSystem.cpp.tpl"] = rootPath + "/src/systems/" + fileName + "System.cpp"
	paths[binPath + "/templates/frameworks/TestFrameworkTpl.hpp.tpl"] = rootPath + "/includes/Nexus/frameworks/" + fileName + "FrameworkTpl.hpp"
	paths[binPath + "/templates/frameworks/FrameworkTest.cpp.tpl"] = frameworkDirectory + "/" + "Framework" + fileName + ".cpp"
	paths[binPath + "/templates/frameworks/FrameworkTest.hpp.tpl"] = frameworkDirectory + "/" + "Framework" + fileName + ".hpp"
	paths[binPath + "/templates/frameworks/CMakeLists.txt.tpl"] = frameworkDirectory + "/CMakeLists.txt"

	upperName = fileName.upper()
	baseName = fileName
	lowerName = fileName.lower()

	if not os.path.exists(frameworkDirectory):
		os.makedirs(frameworkDirectory)
		if not os.path.exists(frameworkBuildDirectory):
			os.makedirs(frameworkBuildDirectory)

	memorize = False

	for key, value in paths.items():
		Inform("About to copy " + key + " as " + value)

		choice = "y"
		if not memorize and os.path.exists(value):
			Warn("The file " + value + " already exist. Do yout to override it?")
			choice = ask(["y", "n"])
			Warn('Do you want to memorize this choice for the next files?')
			memorize = True if ask(["y", "n"]) == 'y' else False
		
		if choice == 'n' and memorize == True:
			break

		if choice == 'n':
			Log("Skipping file...", color='Green', bold=True)
			continue

		shutil.copy2(key, value)
		Log("Success!", color='Green')

		with fileinput.FileInput(value, inplace=True) as file:
			for line in file:
				print(line.replace("${__NX_LOWER_SYSTEM__}", lowerName).replace("${__NX_UPPER_SYSTEM__}", upperName).replace("${__NX_BASE_SYSTEM__}", baseName), end='')
		
	Log("Done", color='Green', bold=True)	

def ask(lRange):
	choice = input("[" + ', '.join(lRange) + "]: ")
	while choice not in lRange:
		choice = input("Please select a correct answer [" + ', '.join(lRange) + "]: ")
	return choice

if __name__ == '__main__':
	Head("SFG is starting...")
	rootPath, sfName, delete = parse(sys.argv[1:])
	try:	
		if (delete):
			deleteFiles(rootPath, sfName)
		else:
			copyFiles(rootPath, sfName)
	except Exception as e:
		Fail(str(e))
	Head("SFG is stopping...")	