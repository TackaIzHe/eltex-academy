int convert(int x, char* binary, int length){
    int index = length;
    int zero = 48;
    int next = x;
    while(next>0){
        binary[index]=(next & 1)+zero;
        next = next>>1;
        index--;
    }
    while(index>=0){
        binary[index] = zero;
        index--;
    }
    return 1;
}
int notBinary(char* binary){
    int index = 7;
    int zero = 48;
    while(index>=0){
        binary[index] = !(binary[index]-zero) + zero;
        index--;
    }
    return 1;
}

int plusOne(char* binary){
    int index = 7;
    int zero = 48;
    while(index>=0){
        if(binary[index]==zero){
            binary[index] += 1;
            break;
        }
        if(binary[index]>zero){
            binary[index] = zero;
        }
        index--;
    }
    return 1;
}

int countOne(char* binary){
    int index = 0;
    int x = 0;
    int one = 49;
    while(index<8){
        if(binary[index]==one){
            x++;
        }
        index++;
    }
    return x;
}

int replaceBinary(int pos, char*intBinary, char*binary){
    int index = 0;
    while(index<8){
        intBinary[pos+index] = binary[index];
        index++;
    }
    return 1;
}

int deconvert(char* binary,int length){
    int result = 1;
    int endPos = 0;
    int one = 49;
    while(binary[endPos] != one){
        endPos++;
        if(endPos>length){
            return 0;
        }
    }
    while(endPos <= length){
        endPos++;
        if(endPos == length + 1){
            return result;
        }
        if(binary[endPos] == one){
            result = (result * 2)+1;
        }
        else{
            result = result * 2;
        }
    }
}