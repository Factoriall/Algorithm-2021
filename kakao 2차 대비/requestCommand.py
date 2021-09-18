import jsonRequests


def requestForTruckCommand(cycles, problem, time):
    data = {'commands': []}

    trucks = jsonRequests.getTrucksResponse()
    for item in trucks['trucks']:
        cmd = {
            "truck_id": item['id'],
            "command": []
        }

        print("location: ", item['location_id'])
        print(item['id'], ": (" + str(4 - item['location_id'] % 5) + "," + str(item['location_id'] // 5)
              + "), loaded:", item['loaded_bikes_count'])
        '''
        0: 6초간 아무것도 하지 않음
        1: 위로 한 칸 이동
        2: 오른쪽으로 한 칸 이동
        3: 아래로 한 칸 이동
        4: 왼쪽으로 한 칸 이동
        5: 자전거 상차
        6: 자전거 하차
        '''

        if time == 0:
            for up in range(item['id']):
                cmd['command'].append(1)
        elif time == 1:
            cmd['command'].append(5)
            for t in range(4):
                cmd['command'].append(2)
                cmd['command'].append(5)
        elif time == 2:
            cmd['command'].append(5)
            for t in range(4):
                cmd['command'].append(4)
                cmd['command'].append(5)
        else:
            loaded = item['loaded_bikes_count']
            lo = []
            hi = []

            for j in range(5):
                cNum = cycles[4 - item['id']][j]
                if cNum < 2:
                    lo.append(j)
                if cNum > 3:
                    hi.append(j)
            maxCnt = 10
            cnt = 0
            truck = item['location_id'] // 5

            if loaded >= 5:
                for lw in lo:
                    dist = truck - lw
                    cd = []
                    abso = abs(dist)
                    if truck - lw < 0:  # 오른쪽, 2
                        while abso > 0:
                            cd.append(2)
                            abso -= 1
                    else:  # 왼쪽, 4
                        while abso > 0:
                            cd.append(4)
                            abso -= 1

                    cycleNum = cycles[4 - item['id']][lw]
                    print("cycleNum:", cycleNum)
                    while cycleNum < 2:
                        if loaded == 0:
                            break
                        cd.append(6)
                        cycleNum += 1

                    if len(cd) < maxCnt - cnt and cycleNum != cycles[4 - item['id']][lw]:
                        truck += (truck - lw)
                        cnt += len(cd)
                        cmd['command'].extend(cd)

                for h in hi:
                    dist = truck - h
                    cd = []
                    abso = abs(dist)
                    if dist < 0:  # 오른쪽, 2
                        while abso > 0:
                            cd.append(2)
                            abso -= 1
                    elif dist > 0:  # 왼쪽, 4
                        while abso > 0:
                            cd.append(4)
                            abso -= 1
                    cycleNum = cycles[4 - item['id']][h]
                    while cycleNum > 3:
                        cd.append(5)
                        cycleNum -= 1

                    if len(cd) < maxCnt - cnt and cycleNum != cycles[4 - item['id']][h]:
                        truck += (truck - h)
                        cnt += len(cd)
                        cmd['command'].extend(cd)
            else:
                for h in hi:
                    dist = truck - h
                    cd = []
                    abso = abs(dist)
                    if dist < 0:  # 오른쪽, 2
                        while abso > 0:
                            cd.append(2)
                            abso -= 1
                    elif dist > 0:  # 왼쪽, 4
                        while abso > 0:
                            cd.append(4)
                            abso -= 1
                    cycleNum = cycles[4 - item['id']][h]
                    while cycleNum > 3:
                        cd.append(5)
                        cycleNum -= 1

                    if len(cd) < maxCnt - cnt and cycleNum != cycles[4 - item['id']][h]:
                        truck += (truck - h)
                        cnt += len(cd)
                        cmd['command'].extend(cd)

                for lw in lo:
                    dist = truck - lw
                    cd = []
                    abso = abs(dist)
                    if truck - lw < 0:  # 오른쪽, 2
                        while abso > 0:
                            cd.append(2)
                            abso -= 1
                    else:  # 왼쪽, 4
                        while abso > 0:
                            cd.append(4)
                            abso -= 1

                    cycleNum = cycles[4 - item['id']][lw]
                    print("cycleNum:", cycleNum)
                    while cycleNum < 2:
                        if loaded == 0:
                            break
                        cd.append(6)
                        cycleNum += 1

                    if len(cd) < maxCnt - cnt and cycleNum != cycles[4 - item['id']][lw]:
                        truck += (truck - lw)
                        cnt += len(cd)
                        cmd['command'].extend(cd)

        data['commands'].append(cmd)

    print(data)

    response = jsonRequests.getSimulationResponse(data)
    print(response)
