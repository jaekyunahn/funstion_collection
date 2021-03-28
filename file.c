/*
 *	File을 특정 위치 에서 부터 읽을 수 있는 Function
 *	sFileAddress	: 읽어 들일 File Address
 *	sReadFileData	: 읽은 Data를 저장 할 변수의 주소값
 *	iStartIndex		: 읽기 시작 할 위치
 *	iReadSize		: 읽어 들일 크기
 */
int fFileReadFunction(char* sFileAddress, char* sReadFileData, int iStartIndex, int iReadSize){
	unsigned int iFileSize = 0;
	FILE* fp = fopen(sFileAddress, "rb");
	if (fp == 0) {
		return -1;
	}
	if (iReadSize == 0){
		fseek(fp, 0, SEEK_END);
		iFileSize = (unsigned int)ftell(fp);
		fseek(fp, 0, SEEK_SET);
		fread(sReadFileData, sizeof(char), iFileSize, fp);
	}
	else{
		//iStartIndex
		fseek(fp, iStartIndex, SEEK_SET);
		fread(sReadFileData, sizeof(char), iReadSize, fp);
	}
	fclose(fp);
	return 0;
}

/*
 *	File을 새로 쓰는 함수 Function
 *	const char* sFileAddress	: 새로 쓰기 할 File 주소와 이름
 *	const char* sWriteFileData	: File에 입력할 Data 주소
 *	int iWriteSize				: File에 입력할 Data 길이
 */
int fFileWriteFunction(const char * sFileAddress, const char * sWriteFileData, int iWriteSize){
	int iFileSize = 0;
	FILE* fp = fopen(sFileAddress, "w");
	if (fp == 0) {
		return -1;
	}
	fwrite(sWriteFileData, sizeof(char), sizeof(char) * iWriteSize, fp);
	fclose(fp);
	return 0;
}

/*
 *	기존 File을 이어 쓰는 함수 Function
 *	const char* sFileAddress	: 이어 쓰기 할 File 주소와 이름
 *	const char* sWriteFileData	: File에 입력할 Data 주소
 *	int iWriteSize				: File에 입력할 Data 길이
 */
int fFileAppendWriteFunction(const char* sFileAddress, const char* sWriteFileData, int iWriteSize){
	int iFileSize = 0;
	FILE* fp = fopen(sFileAddress, "a");
	if (fp == 0) {
		return -1;
	}
	fwrite(sWriteFileData, sizeof(char), sizeof(char) * iWriteSize, fp);
	fclose(fp);
	return 0;
}

//Example
int main(int argc, char** argv){
	unsigned char readData[11] = "";
	
	//wrtie.txt를 최초로 생성 / Data "1234"를 4Byte만큼 저장
	fFileWriteFunction("./write.txt","1234",4);
	
	//write.txt를 시작점 0에서 부터 4Byte를 읽고 printf()분으로 출력하여 확인
	fFileReadFunction("./write.txt", readData, 0, 4);
	printf("readData:%s\r\n", readData);
	
	//wrtie.txt에 Data "5678"을 추가로 4Byte만큼 저장
	fFileAppendWriteFunction("./write.txt", "5678", 4);
	
	//write.txt를 시작점 4에서 부터 4Byte를 읽고 printf()분으로 출력하여 확인
	fFileReadFunction("./write.txt", readData, 4, 4);
	printf("readData:%s\r\n", readData);
	
	//read.txt를 시작점 3에서 부터 10Byte를 읽고 printf()분으로 출력하여 확인
	fFileReadFunction("./read.txt", readData, 3, 10);
	printf("readData:%s\r\n", readData);
}
