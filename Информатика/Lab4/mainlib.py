import yaml
import json
import time

start_time = time.perf_counter()

with open("timetable.json", 'r', encoding='utf-8') as input:
    json_object = json.load(input)
    print(yaml.dump(json_object))

print(time.perf_counter() - start_time)
