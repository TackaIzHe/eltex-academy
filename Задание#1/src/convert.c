int convert(int x, char* binary){
    int index = 7;
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
}