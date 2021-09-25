import json
import requests

BASE_URL = "https://kox947ka1a.execute-api.ap-northeast-2.amazonaws.com/prod/users"
x_auth_token = "24d18310fc8e5ba905a4883b0cd49f29"
auth_key = [None] * 2


def sendStartApi(problem):
    global auth_key
    headers = {'X-Auth-Token': x_auth_token,
               'Content-Type': 'application/json'}
    body = {
        'problem': problem
    }

    response = requests.post(BASE_URL + "/start", headers=headers, data=json.dumps(body))
    print("StartApi response:", response.status_code)

    auth_key[problem - 1] = response.json()['auth_key']


def sendLocationsApi(problem):
    headers = {'Authorization': auth_key[problem-1],
               'Content-Type': 'application/json'}

    response = requests.get(BASE_URL + "/locations", headers=headers)
    print("LocationsApi response:", response.status_code)
    return response.json()


def sendTrucksApi(problem):
    headers = {'Authorization': auth_key[problem-1],
               'Content-Type': 'application/json'}

    response = requests.get(BASE_URL + "/trucks", headers=headers)
    print("TrucksApi response:", response.status_code)
    return response.json()


def sendSimulateApi(problem, data):
    headers = {'Authorization': auth_key[problem-1],
               'Content-Type': 'application/json'}

    response = requests.put(BASE_URL + "/simulate", headers=headers, data=json.dumps(data))
    print("SimulateApi response:", response.status_code)
    print(response.text)


def sendScoreApi(problem):
    headers = {'Authorization': auth_key[problem-1],
               'Content-Type': 'application/json'}

    response = requests.get(BASE_URL + "/score", headers=headers)
    print("ScoreApi response:", response.status_code)
    return response.json()
