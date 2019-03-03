# -*- coding: UTF-8 -*- 

import re

def printDict(_dir):
	for i in _dir.keys():
		print(i, ':', _dir.get(i))
	return

def printList(_list):
	for item in _list:
		print(item[0], ":", item[1])
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
	return _dir

def sort(_dir):
	return sorted(_dir.items(), key = lambda item:item[0])

def main():
	while(True) {
		printList(sort(separate()))
	}

if __name__ == '__main__':
	main()