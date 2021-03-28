/*
 *	Convert Float and String 4 Bytes
 *	union을 이용하여 데이터 형변환. 예를들어 float 같은 데이터를 char 배열로 바꿔서 파일로 저장 하기 유용
 */
union uFloatConvert{
	float uFloatData;
	char uStringData[4];
};

float fConvertString4BytesToFloat32Type(unsigned char* sData){
	union uFloatConvert uF;
	memcpy(uF.uStringData, sData, sizeof(float));
	return uF.uFloatData;
}

void fConvertFloat32TypeToString4Bytes(float fData, unsigned char* sData){
	union uFloatConvert uF;
	uF.uFloatData = fData;
	memcpy(sData, uF.uStringData, sizeof(char) * 4);
}

/*
 *	Square Function.
 */
int fSquareFunction(int iSource, int iSquareCount) {
	int x;
	int res = 1;
	for (x = 0; x < iSquareCount; x++){
		res = res * iSource;
	}
	return res;
}

/*
 *	String Comparison Function. 
 *	같으면 계속 탐색하다가 틀리면 바로 return -1
 */
int fStringComparisonFunction(unsigned char* sDataX, unsigned char* sDataY, int iSerchLength) {
	int x = 0;
	for (x = 0; x < iSerchLength; x++) {
		if (sDataX[x] != sDataY[x]) {
			return -1;
		}
	}
	return 0;
}

/*
 *	String Data를 int32로 변환
 */
#define MAX_STRINGBUFFER	16
int fConvertStringToInt32_autosize(unsigned char* sData) {
	unsigned char sBuffer[MAX_STRINGBUFFER] = "";
	int iResulte = 0;
	int iBufferIndex = 0;
	int i = 0;
	memset(sBuffer, 0x00, sizeof(sBuffer));
	for (i = ZERO; i < MAX_STRINGBUFFER; i++) {
		if ((sData[i] >= 0x30) && (sData[i] <= 0x39)) {
			sBuffer[iBufferIndex] = sData[i];
			iBufferIndex++;
		}
		else if (sData[i] == 0x00) {
			break;
		}
	}
	for (i = ZERO; i < iBufferIndex; i++) {
		iResulte = iResulte * 10;
		iResulte = iResulte + (sBuffer[i] - 0x30);
	}
	return iResulte;
}

/*
 *	string data convert to integer
 *	주로 비트맵 Header같이 연속된 바이너리 값들을 int32로 변환할때 유용
 *	ex)endian=0
 */
#define MAX_BINTOINTBUFFER	256
int fBinToInteger(unsigned char* sData, int iDataSize, int iOffset, int endian) {
	unsigned char data[MAX_BINTOINTBUFFER] = "";
	unsigned int iResult = 0;
	memset(data, 0x00, sizeof(data));
	memcpy(data, sData + iOffset, iDataSize);
	if (endian == 0){
		switch (iDataSize) {
		case 1: 	iResult = data[0]; break;
		case 2: 	iResult = data[0] + (data[1] * 256); break;
		case 3: 	iResult = data[0] + (data[1] * 256) + (data[2] * 65536); break;
		case 4: 	iResult = data[0] + (data[1] * 256) + (data[2] * 65536) + (data[3] * 4294967296); break;
		default: 	break;
		}
	}
	else{
		switch (iDataSize) {
		case 1: 	iResult = data[0]; break;
		case 2: 	iResult = data[1] + (data[0] * 256); break;
		case 3: 	iResult = data[2] + (data[1] * 256) + (data[0] * 65536); break;
		case 4: 	iResult = data[3] + (data[2] * 256) + (data[1] * 65536) + (data[0] * 4294967296); break;
		default: 	break;
		}
	}
	return iResult;
}














