/*ID:5051-6006
  名前：神谷一輝
  課題番号：6
  プログラム解説：argvをつかいプログラム実行時に指定したファイルを使えるようにした。
               標準エラー出力をfprintfの出力先にすることでprintfを使わずにコマンドライン上に出力できた
               データの読み込みはIDを読み込みそれができているかをループ条件にし、一行ずつ読み込んだ
               採点は一文字ずつ比較した
               統計は一要素ずつ足していって出した
  実行例：ne300203@ne300203-VirtualBox:~$ cat answer.dat
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
#define N 256  // 入力ファイル１行は最大２５５文字までとする．
#define M 10   // 問題数は１０個
//#define dataFile "MarkSheets.dat"  基本課題での解答ファイルはmarkSheets.datを指定

void read_answer(FILE *fp, char *ans); // 正解を読み込む関数．正解は配列ansに格納する．
int read_sheets(FILE *fp, char ID[][N], char table[][N]); // 解答ファイルを読み込み，受験者数を関数値とする．
void checkMarkSheet(char string[],char ans[], int binary[]); // 各解答の採点結果は配列binaryに格納する．
void printTable(int total, char ID[][N], int score[][M]);    // 採点結果一覧 scoreを学籍番号IDと共に画面表示する．
void write_summary(int total, char ID[][N], int score[][M]); // 受験生の得点と各問の正答率を表示する．

int main(int argc,char *argv[]){
  FILE *fpr1, *fpr2;  // 解答ファイルmarkSheets.datへのポインタはfpr1，正解ファイルへのポインタはfpr2
  char table[100][N]; // 解答ファイルmarkSheets.datにある各解答を格納する配列
  int  i;          
  int  total;         // 解答ファイルmarkSheets.datの受験者総数
  char ID[100][N];    // 解答ファイルmarkSheets.datの学籍番号を先頭から順に格納する配列
  char ans[M];        // 正解ファイルanswer.datにある正解を格納する配列 
  int  score[100][M]; // 各解答の採点結果を格納する配列
  if( (fpr1=fopen(argv[1],"rt"))==NULL ){
  	printf(stderr,"Read Error : %s\n",argv[1]);
  	return 1;
  }  
  total = read_sheets(fpr1, ID,table);
  if((fpr2=fopen(argv[2],"rt"))==NULL){//空欄を埋めること
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
  
  
  // 変数は追加しないこと．
  // fpが指すファイルの先頭から順に，学籍番号と10問全解答を文字列として読み込みそれぞれ配列IDと
  // 配列tableに格納すること．ファイルの行数を数えることで，受験者総数(total)を特定すること．
  fclose(fp);
  return( total );
}
void checkMarkSheet(char string[], char ans[], int binary[]){
  int j ; // 変数は追加しないこと．
  for(j=0;j<M;j++){
  	if(string[j]==ans[j])
  		binary[j]=1;
  else
  binary[j]=0;// 各問に対して正解ansと解答string を比較し，正解であれば1,不正解であれば0をbinaryに与えること．
  }
}

void write_summary(int total,char ID[][N], int score[][M]){
  int i,j;   // 変数は追加しないこと．
  int sum[100];   // 受験生の得点を格納する配列
  float rate[M];  // 各問の正答率を格納する配列
 // ここからあたりに，各受験生の得点と各問の正答率を計算するプログラムを完成すること．
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
