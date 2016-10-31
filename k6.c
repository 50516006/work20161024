/*ID:5051-6006
  ���O�F�_�J��P
  �ۑ�ԍ��F6
  �v���O��������Fargv�������v���O�������s���Ɏw�肵���t�@�C�����g����悤�ɂ����B
               �W���G���[�o�͂�fprintf�̏o�͐�ɂ��邱�Ƃ�printf���g�킸�ɃR�}���h���C����ɏo�͂ł���
               �f�[�^�̓ǂݍ��݂�ID��ǂݍ��݂��ꂪ�ł��Ă��邩�����[�v�����ɂ��A��s���ǂݍ���
               �̓_�͈ꕶ������r����
               ���v�͈�v�f�������Ă����ďo����
  ���s��Fne300203@ne300203-VirtualBox:~$ cat answer.dat
acbaccadca
ne300203@ne300203-VirtualBox:~$ cat ms.dat 
36753562
bbcdcddcac
26187920
cdddbcccbd
36129319
abcadcbcda
63206155
adabcbbbad
25474430
daacaaddcd
20689266
cddcccdbbc
72261061
bbadabdbbd
15977673
cbcddaadab
39088509
adcbcdbdda
48103044
acdadddbda
ne300203@ne300203-VirtualBox:~$ ./a.out  ms.dat  answer.dat
========= Table ========
36753562
0000100000
26187920
0000010000
36129319
1001010001
63206155
1000100000
25474430
0000000110
20689266
0000110000
72261061
0000000000
15977673
0000001100
39088509
1000100101
48103044
1101000001
========================
========= Summary ========
 1:0.4
 2:0.1
 3:0.0
 4:0.2
 5:0.4
 6:0.3
 7:0.1
 8:0.3
 9:0.1
10:0.3
36753562: 1
26187920: 1
36129319: 4
63206155: 2
25474430: 2
20689266: 2
72261061: 0
15977673: 2
39088509: 4
48103044: 4
==========================
*/
#include<stdio.h>
#define N 256  // ���̓t�@�C���P�s�͍ő�Q�T�T�����܂łƂ���D
#define M 10   // ��萔�͂P�O��
//#define dataFile "MarkSheets.dat"  ��{�ۑ�ł̉𓚃t�@�C����markSheets.dat���w��

void read_answer(FILE *fp, char *ans); // ������ǂݍ��ފ֐��D�����͔z��ans�Ɋi�[����D
int read_sheets(FILE *fp, char ID[][N], char table[][N]); // �𓚃t�@�C����ǂݍ��݁C�󌱎Ґ����֐��l�Ƃ���D
void checkMarkSheet(char string[],char ans[], int binary[]); // �e�𓚂̍̓_���ʂ͔z��binary�Ɋi�[����D
void printTable(int total, char ID[][N], int score[][M]);    // �̓_���ʈꗗ score���w�Дԍ�ID�Ƌ��ɉ�ʕ\������D
void write_summary(int total, char ID[][N], int score[][M]); // �󌱐��̓��_�Ɗe��̐�������\������D

int main(int argc,char *argv[]){
  FILE *fpr1, *fpr2;  // �𓚃t�@�C��markSheets.dat�ւ̃|�C���^��fpr1�C�����t�@�C���ւ̃|�C���^��fpr2
  char table[100][N]; // �𓚃t�@�C��markSheets.dat�ɂ���e�𓚂��i�[����z��
  int  i;          
  int  total;         // �𓚃t�@�C��markSheets.dat�̎󌱎ґ���
  char ID[100][N];    // �𓚃t�@�C��markSheets.dat�̊w�Дԍ���擪���珇�Ɋi�[����z��
  char ans[M];        // �����t�@�C��answer.dat�ɂ��鐳�����i�[����z�� 
  int  score[100][M]; // �e�𓚂̍̓_���ʂ��i�[����z��
  if( (fpr1=fopen(argv[1],"rt"))==NULL ){
  	printf(stderr,"Read Error : %s\n",argv[1]);
  	return 1;
  }  
  total = read_sheets(fpr1, ID,table);
  if((fpr2=fopen(argv[2],"rt"))==NULL){//�󗓂𖄂߂邱��
  	fprintf(stderr," Read Error : %s\n",argv[2]);
  	return 1;
  }  
  read_answer(fpr2,ans);
  for(i=0; i<total ; i++) 
  	checkMarkSheet(table[i], ans, score[i]);
  fprintf(stderr,"========= Table ========\n");  
  printTable(total, ID, score);
  fprintf(stderr,"========================\n");
  fprintf(stderr,"========= Summary ========\n");
  write_summary(total, ID, score);
  fprintf(stderr,"==========================\n");
}
void read_answer(FILE *fp, char *ans){
  int j;
  for(j=0 ;j < M; j++) fscanf(fp,"%c",&ans[j]);
  	fclose(fp); 
}
int  read_sheets(FILE *fp, char ID[][N], char table[][N]){
  int i, j=0, total=0; 
  for(i=0;fgets(ID[j],N,fp)!=NULL;i++){
  	fgets(table[j],N,fp);
  	j++;
  }
  total=j;
  
  
  // �ϐ��͒ǉ����Ȃ����ƁD
  // fp���w���t�@�C���̐擪���珇�ɁC�w�Дԍ���10��S�𓚂𕶎���Ƃ��ēǂݍ��݂��ꂼ��z��ID��
  // �z��table�Ɋi�[���邱�ƁD�t�@�C���̍s���𐔂��邱�ƂŁC�󌱎ґ���(total)����肷�邱�ƁD
  fclose(fp);
  return( total );
}
void checkMarkSheet(char string[], char ans[], int binary[]){
  int j ; // �ϐ��͒ǉ����Ȃ����ƁD
  for(j=0;j<M;j++){
  	if(string[j]==ans[j])
  		binary[j]=1;
  else
  binary[j]=0;// �e��ɑ΂��Đ���ans�Ɖ�string ���r���C�����ł����1,�s�����ł����0��binary�ɗ^���邱�ƁD
  }
}

void write_summary(int total,char ID[][N], int score[][M]){
  int i,j;   // �ϐ��͒ǉ����Ȃ����ƁD
  int sum[100];   // �󌱐��̓��_���i�[����z��
  float rate[M];  // �e��̐��������i�[����z��
 // �������炠����ɁC�e�󌱐��̓��_�Ɗe��̐��������v�Z����v���O�������������邱�ƁD
  for(j=0;j<M;j++){
  rate[j]=0;
        for(i=0;i<total;i++){
        rate[j]=rate[j]+score[i][j];}
       rate[j]=rate[j]/total; 
  }
    for(j=0;j<total;j++){
  sum[j]=0;
        for(i=0;i<M;i++){
        sum[j]=sum[j]+score[j][i];}
  }
  for(j=0; j<M; j++) fprintf(stderr,"%2d:%2.1f\n",j+1,rate[j]);
  for(i=0; i<total; i++){
  for(j=0;(ID[i][j]!='\n')&&(ID[i][j]!='\r'); j++) {
        fprintf(stderr,"%c",ID[i][j]);
  }
    fprintf(stderr,":%2d\n",sum[i] ); 
  }
}
void printTable(int total, char ID[][N], int score[][M]){
  int i,j;
  for(i=0; i<total ; i++){ 
    printf("%s",ID[i]); 
    for(j=0; j<M; j++){
      printf("%d",score[i][j]);  
    }
    printf("\n");
  }
}
