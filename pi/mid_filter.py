#coding=utf-8

def median_filter(data):
    return sorted(data)[len(data)/2]

if __name__ == '__main__':
    data = [7,6,0,3000,6];
    print median_filter(data);
