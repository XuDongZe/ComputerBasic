# -*- coding: UTF-8 -*- 

import re

def printDict(_dir):
	for i in _dir.keys():
		print(i, ':', _dir.get(i))
	return

def separate():
	pattern = r'[\[](.*)[\]]'
	p = re.compile(pattern, re.I)
	_dir = {}
	with open(".//glossary.gl", encoding="UTF-8") as file:
		lines = file.readlines()
	for line in lines:
		res = p.search(line).group(1).split(":")
		_dir[res[0].strip()] = res[1].strip()
	return _dir; 

def main():
	printDict(separate())

if __name__ == '__main__':
	main()