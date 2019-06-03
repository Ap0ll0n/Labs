    #include <stdio.h>
    #include <fstream>
    #include <conio.h>
    #include <string.h>
    #include <locale.h>
    #define ID3_MAX_SIZE 128
    #include <iostream>
    #include <Windows.h>
    typedef struct IDv3Tag
    {
        char signature[3];
        char name[30];
        char artist[30];
        char album[30];
        char year[4];
        char description[30];
        unsigned short ganre;
        void show();
        void put();
        } ID3TAG;
     
void view_files();
void view_files()
{
	using namespace std;
	wchar_t fileway[50];
    WIN32_FIND_DATAW wfd;
 	
 	
 	cout << "Enter the way to the directory like: Disc_name:\\path\\*: ";
 	wcin >> fileway;
    HANDLE const hFind = FindFirstFileW(fileway, &wfd);
 
    if (INVALID_HANDLE_VALUE != hFind)
    {
        do
        {
            std::wcout << &wfd.cFileName[0] << std::endl;
        } while (NULL != FindNextFileW(hFind, &wfd));
 
        FindClose(hFind);
    }
}
     
    long idv3_file_offset(FILE* fp)
    {
        fseek(fp, 0L, SEEK_END); //указатель в конце файла
        return ftell(fp) - 128;	//вернуть значение на 128 меньше конца файла
    }
	 
void IDv3Tag::put(){
	using namespace std;
	string tmp;
	cout << "Enter song`s info: \n";
	cout << "Name: ";
	cin.width(30);
	cin.fill(' ');
	getline(cin,tmp);
	for(int i = 0; i < tmp.size(); i++){
		name[i] = tmp[i];
	}
		for(int i = tmp.size(); i < 30; i++)
	{
		name[i] = ' ';	
	}
	name[29] = '\0';
	
	cout << "\nArtist: ";
	getline(cin, tmp);
	for(int i = 0; i < tmp.size(); i++)
		artist[i] = tmp[i];
	for(int i = tmp.size(); i < 30; i++)
		{
			artist[i] = ' ';	
		}
	artist[29] = '\0';
	
	cout << "\nAlbum: ";
	getline(cin, tmp);
	for(int i = 0; i < tmp.size(); i++)
		album[i] = tmp[i];
	for(int i = tmp.size(); i < 30; i++)
		album[i] = ' ';	
	album[29] = '\0';
	
	cout << "\nYear: ";
	getline(cin, tmp);
	for(int i = 0; i < tmp.size(); i++)
		year[i] = tmp[i];

	
		
	cout << "\nDescription: ";
	getline(cin, tmp);
	for(int i = 0; i < tmp.size(); i++)
		description[i] = tmp[i];
	for(int i = tmp.size(); i < 30; i++)
		name[i] = ' ';	
	description[29] = '\0';
	
	cout << "\nGanre(a number from 0 to ...): ";
	cin >> ganre;
} 
    
void IDv3Tag::show(){
	name[29] = '\0';
	
	std::cout << "Name: " << name << "\nArtist: " << artist << "\nAlbum: " << album << "\nYear: ";
	for(int i = 0; i < 4; i++)
		std::cout << year[i];
	std::cout << "\nDescription: " << description << "\nGanre: " << ganre << '\n';
}   
    void Menu(int &answer){
    	using namespace std;
		cout << "Enter what you want to do: ";
		cout << "\n1 - to get metadata\n2 - to put metadata\n";
		cout << "3 - to view files in directory\n";
		cout << "4 - to exit\n";
		for(;;){
			cin >> answer;
			if(answer > 0 && answer < 5)
				break;
		}
		cin.ignore();
	} 
     
     
    int main()
    {
    	system("color f0");
    	setlocale(LC_ALL, "");
    	int answer;
    	IDv3Tag obj1;
    	std::string file;
    	
    	system("cls");
    	while(answer != 4){
    	Menu(answer);
    	switch(answer){
    	case 1:{
    			std::cout << "Enter name of the file: ";
    			getline(std::cin, file);
    			char filename[file.size()];
    			for(int i = 0; i < file.size(); i++)
    				filename[i] = file[i];
		    	FILE* fp = NULL; 
		        if ((fp = fopen(filename,"r")) == NULL)
		        std::cout << "Unable to open file %s for reading\n" << filename;
		        char* buf = new char[128];
		     	fseek(fp, idv3_file_offset(fp), SEEK_SET);
		       	fread(buf, 1, 128, fp);
		       	for(int i = 3, j = 0; j < 31, i < 31; j++, i++)
					obj1.name[j] = buf[i];		
				for(int i = 33, j = 0; j < 31, i < 61; i++, j++)
					obj1.artist[j] = buf[i];
				for(int i = 63, j = 0; j < 31, i < 91; i++, j++)
					obj1.album[j] = buf[i];
				for(int i = 93, j = 0; j < 5, i < 97; i++, j++)
					obj1.year[j] =  buf[i];
				for(int i = 97, j = 0; j < 31, i < 128; j++, i++)
					obj1.description[j] = buf[i];
				obj1.ganre = buf[127];
				obj1.show();
				fclose(fp);
				
				break;
				}
		case 2:{
				IDv3Tag tempobj;
				char filename[file.size()];
				std::string temp;
    			for(int i = 0; i < file.size(); i++)
    				filename[i] = file[i];
				std::string str;
				std::ofstream ofs("temp.txt", std::ios::binary);
				std::ifstream get("temp.txt", std::ios::binary);
    			std::ifstream ifs(filename, std::ios::binary);
    			while(getline(ifs,str)){
    				ofs << str << '\n';
				}
				tempobj.put();
				ifs.close();
				ofs.close();
				tempobj.show();
    			std::ofstream change(filename, std::ios::binary);
    			while(getline(get,str)){
    				for(int i = 0; i < str.size(); i++){
    					if(str[i] == 'T' && str[i+1] == 'A' && str[i+2] == 'G')
    						{
    							
    							for(int j = 0; j < str.size() - 128; j ++)
    								temp[j] = str[j];
    							str = temp;
    							break;
							}
					}
					
    				change << str << '\n';
				}
				change.seekp(-126, std::ios::end);
				change << tempobj.name << tempobj.artist << tempobj.album << tempobj.year << tempobj.description << tempobj.ganre;
				break;
	  }
	  	case 3:{
	  		view_files();
			break;
		  }
		case 4:{
			exit(0);
			break;
		}
	 }
	}
    	
    	
        _getch();
        return 0;
    }

 
