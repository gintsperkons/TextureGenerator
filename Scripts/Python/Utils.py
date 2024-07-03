import os
import sys
sys.path.append(f'Scripts/Python')
import Defines
import requests

def testDir(path):
    if not os.path.exists(path):
        os.makedirs(path)

def formatSize(size):
    power = 2**10
    n = 0
    power_labels = {0 : 'B', 1: 'KB', 2: 'MB', 3: 'GB', 4: 'TB'}
    while size > power:
        size /= power
        n += 1
    return f'{size:.2f} {power_labels[n]:<7}'

def downloadFile(url, path):
    testDir(os.path.dirname(path))
    with open(path, "wb") as f:
        print("Downloading %s" % path)
        response = requests.get(url, stream=True)
        total_length = response.headers.get('content-length')

        if total_length is None: # no content length header
            f.write(response.content)
        else:
            dl = 0
            total_length = int(total_length)
            for data in response.iter_content(chunk_size=4096):
                dl += len(data)
                f.write(data)
                done = int(50 * dl / total_length)
                sys.stdout.write("\r[%s%s] %s" % ('=' * done, ' ' * (50-done), formatSize(dl)))
                sys.stdout.flush()
