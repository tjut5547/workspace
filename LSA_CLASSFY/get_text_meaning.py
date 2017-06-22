import os

if __name__ == '__main__':

	SUM = 0

	folder_path = './文档'
	folder_list = os.listdir(folder_path)

	for folder in folder_list:
		new_folder_path = os.path.join(folder_path, folder)
		file_list = os.listdir(new_folder_path)

		SUM = 0
		for file in file_list:
			file_name = os.path.join(new_folder_path, file)
			with open(os.path.join(new_folder_path, file), 'r',) as fp:
				try:
					context = fp.read()
				except:
					fp.close()
					SUM += 1
					os.system("rm " + file_name)

		print (folder)
		print ("sum = ", SUM)
