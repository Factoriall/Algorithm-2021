from rest_api import *
from calculate_module import *


def main():
    prob = 1
    sendStartApi(prob)
    for i in range(720):
        locations = sendLocationsApi(prob)['locations']
        bikes = convertIntoMap(locations, prob)
        trucks = sendTrucksApi(prob)['trucks']
        showTruckLocation(prob, trucks)

        move_truck(prob, i, bikes, trucks)


    score = sendScoreApi(prob)['score']


if __name__ == '__main__':
    main()


