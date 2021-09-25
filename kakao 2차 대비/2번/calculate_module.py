from rest_api import sendSimulateApi
from queue import PriorityQueue


def convertIntoMap(locations, problem):
    mapLen = getLength(problem)
    bikes = [[0] * mapLen for i in range(mapLen)]
    idx = 0
    for item in locations:
        bId = item['id']
        bikes[(mapLen - 1) - (bId % mapLen)][bId // mapLen] = item['located_bikes_count']
        idx += 1

    return bikes


def showTruckLocation(problem, trucks):
    mapLen = getLength(problem)

    for truck in trucks:
        tId = truck['location_id']
        i = (mapLen - 1) - (tId % mapLen)
        j = tId // mapLen
        print(str(truck['id']) + ": (" + str(i) + "," + str(j) + ")")


def move_truck(problem, sec, bikes, trucks):
    if problem == 1:
        ret = move_1(sec, bikes, trucks)
    else:
        ret = move_2(sec, bikes, trucks)
    print(ret)
    sendSimulateApi(problem, ret)


'''
0: 6초간 아무것도 하지 않음
1: 위로 한 칸 이동
2: 오른쪽으로 한 칸 이동
3: 아래로 한 칸 이동
4: 왼쪽으로 한 칸 이동
5: 자전거 상차
6: 자전거 하차
'''


def move_1(sec, bikes, trucks):
    length = 5
    send = {
        "commands": []
    }
    for truck in trucks:
        dirCmd = []
        truck_id = truck['id']
        if sec == 0:
            for i in range(truck_id):
                dirCmd.append(1)

        elif sec == 1:
            dirCmd.append(5)
            for i in range(4):
                dirCmd.append(2)
                dirCmd.append(5)
        else:
            dirCmd = moveByIncident_1(bikes, truck)

        cmd = {
            'truck_id': truck_id,
            "command": dirCmd
        }
        send['commands'].append(cmd)

    return send


MAX = 10


def loadBike(bikes, r, now, loaded, ret, avg):
    print("load", avg)
    MIdx = -1
    MLoad = 1
    MDist = 0
    isLeft = False
    isFin = False
    for i in range(5):
        if MLoad < bikes[r][i]:
            MLoad = bikes[r][i]
            MIdx = i
            MDist = abs(i - now)
            isLeft = (i - now < 0)
    if MIdx != -1 and avg > bikes[r][MIdx]:
        if isLeft:
            d = 4
        else:
            d = 2
        move = 0
        while len(ret) < MAX and MDist != move:
            if isLeft: now -= 1
            else: now += 1
            move += 1
            ret.append(d)
        if len(ret) != MAX:
            if avg == 0:
                while loaded < bikes[r][MIdx] and len(ret) < MAX:
                    loaded += 1
                    bikes[r][MIdx] -= 1
                    ret.append(5)
            else:
                while len(ret) < MAX and avg < bikes[r][MIdx]:
                    loaded += 1
                    bikes[r][MIdx] -= 1
                    ret.append(5)
        else:
            isFin = True
    else:
        isFin = True
    return loaded, ret, bikes, now, isFin


def addBike(bikes, r, now, loaded, ret, zero_bike):
    print("addBike", zero_bike)
    mDist = 5
    mIdx = -1
    isLeft = False
    isFin = False
    if loaded != 0 and len(zero_bike) != 0:
        for zb in zero_bike:
            if abs(zb - now) < mDist:
                mDist = abs(zb - now)
                isLeft = (zb - now < 0)
                mIdx = zb
    else:
        for i in range(5):
            if abs(i - now) < mDist:
                mDist = abs(i - now)
                isLeft = (i - now < 0)
                mIdx = i
    if mDist < MAX - len(ret) and bikes[r][mIdx] < 2:
        if isLeft:
            d = 4
        else:
            d = 2
        for i in range(mDist):
            if isLeft: now -= 1
            else: now += 1
            ret.append(d)
        while len(ret) < MAX and bikes[r][mIdx] < 2 and loaded > 0:
            ret.append(6)
            bikes[r][mIdx] += 1
            loaded -= 1
    else:
        isFin = True
    return loaded, ret, bikes, now, isFin


def moveByIncident_1(bikes, truck):
    ret = []
    tId = truck['location_id']
    loaded = truck['loaded_bikes_count']
    r = 4 - (tId % 5)  # 고정
    now = tId // 5
    std = 2
    while len(ret) < MAX:
        zero_bike = []
        isFin = False
        for i in range(5):
            if bikes[r][i] == 0:
                zero_bike.append(i)
        if loaded == 0:  # 무조건 많은 곳에서 load 늘리기
            print("bad")
            loaded, ret, bikes, now, isFin = loadBike(bikes, r, now, loaded, ret, 0)
        elif len(zero_bike) != 0:  # 무조건 없는 곳 보충
            print("zero")
            loaded, ret, bikes, now, isFin = addBike(bikes, r, now, loaded, ret, zero_bike)
        else:  # 밸런싱
            print("balance")
            total = 0
            for i in range(5):
                total += bikes[r][i]
            avg = total // 5
            if avg >= std:
                loaded, ret, bikes, now, isFin = loadBike(bikes, r, now, loaded, ret, avg)
            else:
                loaded, ret, bikes, now, isFin = addBike(bikes, r, now, loaded, ret, [])
        print(loaded, ret, bikes, now, isFin)
        if isFin:
            break

    return ret


def move_2(sec, bikes, trucks):
    length = 5
    send = {
        "commands": []
    }
    return send


def getLength(problem):
    if problem == 1:
        return 5
    else:
        return 60
