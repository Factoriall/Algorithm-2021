import json
import requests

base_url = "https://kox947ka1a.execute-api.ap-northeast-2.amazonaws.com/prod/users"
auth_key = ""


def getStartResponse(p):
    global auth_key
    x_auth_token = "516510ceac3817584d46e66b09ecc751"
    queryString = {"problem": p}
    header = {'Content-Type': 'application/json',
              "X-Auth-Token": x_auth_token}

    r = requests.post(base_url + "/start", headers=header, params=queryString)
    auth_key = json.loads(r.text)['auth_key']
    #print(r.status_code)


def getLocationResponse():
    header = {'Content-Type': 'application/json',
              "Authorization": auth_key}

    r = requests.get(base_url + "/locations", headers=header)
    #print(r.status_code)
    return json.loads(r.text)


def getTrucksResponse():
    header = {'Content-Type': 'application/json',
              "Authorization": auth_key}

    r = requests.get(base_url + "/trucks", headers=header)
    #print(r.status_code)
    return json.loads(r.text)


def getSimulationResponse(data):
    header = {'Content-Type': 'application/json',
              "Authorization": auth_key}

    r = requests.put(base_url + "/simulate", headers=header, data=json.dumps(data))
    print(r.status_code)
    return json.loads(r.text)


def getScore():
    global base_url
    header = {'Content-Type': 'application/json',
              "Authorization": auth_key}

    r = requests.get(base_url + "/score", headers=header)
    #print(r.status_code)
    return json.loads(r.text)
