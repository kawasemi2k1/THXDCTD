#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//chuyen chu hoa thanh chu thuong
void lowercase(char *word){
    int i;
    for(i = 0; word[i] != '\0'; i++){
        if(word[i] >= 'A' && word[i] <= 'Z') word[i] += 32;
    }
}

// tim ky tu dac biet,thuoc a-z, A-Z thi tra ve false, la ky tu dac biet thi return true
bool kyTuDB(char word){
    if((word >= 'a' && word <='z')||(word >= 'A'&& word <= 'Z')) return false;
    return true;
}

//Trong tu co ky tu la ko phai (chu, so) thi xoa
void removeSpecialCharacters(char *word){
    int i, j;
    for(i = 0; word[i] != '\0'; i++){
        while(!(word[i] >= 'a' && word[i] <= 'z') && !(word[i] >= 'A' && word[i] <= 'Z') && (word[i] != '\0') && !(word[i] >= '0' && word[i] <= '9')){
            for(j = i; word[j] != '\0'; j++){
                word[j] = word[j+1];
            }
            word[j] = '\0';
        }
    }
}

int meanninglessWordorNumber(char *word){
    char temp[200], temp2[200];
    strcpy(temp, word);
    lowercase(temp);
    FILE *f = fopen("stopw.txt", "r");
    if(!f) {
        printf("Ko the mo file stopw.txt!\n");
        exit(1);
    }
    while(fscanf(f, "%s", temp2) == 1){
        removeSpecialCharacters(temp);
        if(strcmp(temp, temp2) == 0){
        fclose(f);
        return 1;
    }
        if(temp[0] >= '0' && temp[0] <= '9'){
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

//Ky tu dau viet hoa thi return true, chu thuong thi return false
bool vietHoaKyTuDau(char *test){
    char temp[200];
    strcpy(temp, test);
    removeSpecialCharacters(temp);
    if(temp[0] >= 'A' && temp[0] <= 'Z') return true;
    else return false;
}
    
void main(){
    char words[2000][2000], words2[2000][2000], temp[2000], line[5000];
    int i = 0, next = 0, a, b, c, d, n;
    int linenumber = 1,count = 0;
    FILE *f = fopen("vanban.txt", "r");
    if(!f) {
        printf("Khong the mo file vanban.txt!\n");
        exit(1);
    }
    
    while(fscanf(f, "%s", temp) == 1){
        if(meanninglessWordorNumber(temp) == 0){
            if(next == 1 && vietHoaKyTuDau(temp)){
                if(temp[strlen(temp) - 1] != '.' || strcmp(temp, "U.S.") == 0) continue;
                else{
                    next = 0;
                    continue;
                }
            }
            if(temp[strlen(temp)-1] != '.'){
            next = 1;
            strcpy(words[i], temp);
            removeSpecialCharacters(words[i]);
            lowercase(words[i]);
            i++;
            }else if(strcmp(temp, "U.S.") != 0){
                next = 0;
                strcpy(words[i], temp);
                removeSpecialCharacters(words[i]);
                lowercase(words[i]);
                i++;
            }
        
        }
    }
    for(a = 0;a < i; a++){
        for(b = a + 1;b < i; b++){
            if(strcmp(words[a], words[b]) > 0){
                strcpy(temp, words[a]);
                strcpy(words[a], words[b]);
                strcpy(words[b], temp);
            }
        }
    }
    b = 0;
    for(a = 0; a < i; a++) if(strcmp(words[a], words[a+1]) != 0) strcpy(words2[b++], words[a]);
    strcpy(words2[b], words[i]);
    fseek(f, 0, SEEK_SET);
    for(c = 0; c < b; c++){
        fseek(f, 0, SEEK_SET);
        printf("%s ",words2[c]);
            while(fscanf(f,"%s",temp) == 1){
                removeSpecialCharacters(temp);
                lowercase(temp);
                if(strcmp(words2[c], temp) == 0) count++;
            }
        fseek(f, 0, SEEK_SET);
        printf(" %d",count);
        count = 0;
            while(fgets(line, 256, f) != NULL){
                a = 0;
                n = strlen(line);
                    while(a < n){
                    d = 0;
                    while( a < n && d < strlen( words2[c] ) && ( line[a] == words2[c][d] || line[a] + 32 == words2[c][d] ) ){
                            a++;
                            d++;
                        }
                    if( (a == n||kyTuDB(line[a])==1) && d == strlen( words2[c] ) ) 
                    {
                        
                        printf(",%d", linenumber);
                    }
                    while(a < n && line[a] != ' ') a++;
                    a++;
                    }
        linenumber++;
    }
    printf("\n");
    linenumber = 1;
    }
    fclose(f);
}