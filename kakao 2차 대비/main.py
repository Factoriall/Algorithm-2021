import jsonRequests
from requestCommand import requestForTruckCommand

cycles = [[0 for x in range(5)] for y in range(5)]


def main():
    problem = 1
    jsonRequests.getStartResponse(problem)

    for time in range(720):
        locations = jsonRequests.getLocationResponse()
        # print(locations)
        for item in locations['locations']:
            id = item['id']
            cycles[4 - (id % 5)][id // 5] = item['located_bikes_count']

        for i in reversed(range(5)):
            for j in range(5):
                print(cycles[i][j], end=' ')
            print()
        print()

        requestForTruckCommand(cycles, problem, time)

    score = jsonRequests.getScore()['score']
    print("score: ", score)


if __name__ == '__main__':
    main()
