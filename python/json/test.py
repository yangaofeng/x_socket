import json

def parse_node(cfg):
    print cfg['name']
    print cfg['config']['enable']
    print cfg['config']['ip']
    print cfg['config']['port']


if __name__ == "__main__":
    f = file("node.json")
    cfg = json.load(f)
    f.close()

    parse_node(cfg)

