import gc
import sys
import json
import math
import numpy as np
from os import listdir
from os.path import isfile, join
from matplotlib import pyplot as plt

def get_files_paths(base_path):
    return ['{}/{}'.format(base_path, f) for f in listdir(base_path) if isfile(join(base_path, f)) and '.json' in f ]

def get_json(path):
    ### Reads json file

    f = open(path, 'r')
    json_data = json.loads(f.read())
    f.close()
    return (json_data["config"], json_data["data"])

def get_link_usage(entry, _):
    return entry["linkUsage"]["tx"]

def get_throughput(connection):
    return connection["iperf"]["end"]["sum_sent"]["bits_per_second"] / 1000

def get_retransmits(connection):
    return connection["iperf"]["end"]["sum_sent"]["retransmits"]

def get_connections(entry, algorithm):
    ### Compile result connections into single array

    results = entry["results"]
    connections = []
    for r in results:
        for i in r:
            connections.append(i)

    if not algorithm:
        return connections

    return [ c for c in connections if c['algo'] == algorithm ]

def get_average_throughput(entry, filter):
    ### Get average throughput of connections

    connections = get_connections(entry, filter)
    tts = [ get_throughput(c) for c in connections ]
    return sum(tts) / len(tts) if len(tts) > 0 else 0

def get_retransmits_sum(entry, filter):
    ### Get retransmits of connections

    connections = get_connections(entry, filter)
    tts = [ get_retransmits(c) for c in connections ]
    return sum(tts)

def standard_dev(l):
    avrg = np.average(l)
    return math.sqrt(sum([ math.pow((i - avrg), 2.0) for i in l]) / len(l))

def plot(xvalues, yvalues, algorithm, color, ecolor=''):
    ### Plots one graphic line using matplotlib

    ecolor = color if not ecolor else ecolor
    yvalues_list = np.transpose(np.array(yvalues))
    yvalues = [ np.average(l) for l in yvalues_list ]
    yvalues = [ l for l in yvalues if l != 0 ]

    if not yvalues:
        return

    size = len(yvalues)
    yvalues_error = [ 1.96 * standard_dev(i) / math.sqrt(size) for i in yvalues_list ]

    # plt.plot(xvalues, yvalues, label=algorithm.upper())
    plt.errorbar(xvalues, yvalues ,yerr = yvalues_error, fmt="-", label=algorithm.upper(), ecolor=ecolor, capsize=2, color=color)

def save_and_show(base_path, name, labels, config):
    ### Save the file

    plt.grid(color='silver')
    plt.xlabel('Nº de conexões')
    plt.ylabel(labels['yaxis'])
    plt.title(labels['title'].format(config["LINK_OPTS"]["bw"], int(100 * float(config["BBR_PERCENTAGE"])), int(100 * float(config["CUBIC_PERCENTAGE"]))))

    plt.legend(fontsize = 10, loc='best', fancybox=True, shadow=True, bbox_to_anchor=(0.55,0.6)) # 0.65,0.5

    path = base_path + name + base_path.replace('/', '') + '.png'
    plt.savefig(path, bbox_inches = 'tight')
    # plt.show()

### Enumeration of graphic types
GRAPHIC_TYPES = {
    'utilization': {
        'title': '[{}Mbps] Gráfico de Utilização do enlace x Nº de conexões ({}% BBR, {}% CUBIC)',
        'yaxis': 'Utilização do enlace (Mbps)',
        'yvaluefunc': get_link_usage,
    },
    'throughput': {
        'title': '[{}Mbps] Gráfico de Vazão média x Nº de conexões ({}% BBR, {}% CUBIC)',
        'yaxis': 'Vazão média (Kbps)',
        'yvaluefunc': get_average_throughput,
    },
    'retransmits': {
        'title': '[{}Mbps] Gráfico de Retransmissões X Nº de conexões ({}% BBR, {}% CUBIC)',
        'yaxis': 'Retransmissões (segmentos)',
        'yvaluefunc': get_retransmits_sum,
    }
}

def main():
    base_path = sys.argv[2]
    graphic_type = GRAPHIC_TYPES[sys.argv[1]]

    xvalues = []
    scenario = {}
    yvalues_list = []
    by_percentage = {
        'bbr': {
            10: [],
            20: [],
            30: [],
        },
        'cubic': {
            10: [],
            20: [],
            30: [],
        }
    }

    for p in get_files_paths(base_path):
        # print("FILE: ", p)
        scenario, data = get_json(p)

        yvalues = []
        bbr_results = []
        cubic_results = []
        for entry in data:
            xvalues.append(entry["connections"])
            yvalues.append(graphic_type['yvaluefunc'](entry, ''))
            bbr_results.append(graphic_type['yvaluefunc'](entry, 'bbr'))
            cubic_results.append(graphic_type['yvaluefunc'](entry, 'cubic'))

        yvalues_list.append(yvalues)
        bandwidth = scenario["LINK_OPTS"]["bw"]
        udp_bandwidth = scenario["UDP_BANDWIDTH"]
        udp_percentage = int(100 *udp_bandwidth / float(bandwidth))
        by_percentage['bbr'][udp_percentage].append(bbr_results)
        by_percentage['cubic'][udp_percentage].append(cubic_results)

    xvalues = list(dict.fromkeys(xvalues))
    if sys.argv[1] == 'utilization':
        plot(xvalues, yvalues_list, 'Utilização (Mbps)', 'blue')
    else:
        ### For simple comparison in UDP percentage
        # udp_percent = int(100 * scenario["UDP_BANDWIDTH"] / float(scenario["LINK_OPTS"]["bw"]))
        # plot(xvalues, by_percentage['bbr'][udp_percent], 'BBR ({}% UDP)'.format(udp_percent), 'blue', 'lightgrey')
        # plot(xvalues, by_percentage['cubic'][udp_percent], 'CUBIC ({}% UDP)'.format(udp_percent), 'orange', 'lightgrey')

        ### For all of percentage in the same chart
        plot(xvalues, by_percentage['bbr'][10], 'BBR (10% UDP)', 'midnightblue')
        plot(xvalues, by_percentage['bbr'][20], 'BBR (20% UDP)', 'yellow')
        plot(xvalues, by_percentage['bbr'][30], 'BBR (30% UDP)', 'darkgrey')
        plot(xvalues, by_percentage['cubic'][10], 'CUBIC (10% UDP)', 'deeppink')
        plot(xvalues, by_percentage['cubic'][20], 'CUBIC (20% UDP)', 'orange')
        plot(xvalues, by_percentage['cubic'][30], 'CUBIC (30% UDP)', 'crimson')

    save_and_show(base_path, sys.argv[1], graphic_type, scenario)
    del by_percentage
    del yvalues_list
    del scenario
    del xvalues
    # del data
    gc.collect()

if __name__ == "__main__":
    main()
