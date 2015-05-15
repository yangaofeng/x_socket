#!/usr/bin/python2.6
# coding: utf-8
import sys
#import socket
from os.path import join

from zkclient import ZKClient, zookeeper, watchmethod, ZKClientError

class LcsZookeeper(object):

    ROOT = "/lcs"
    IDC_NAME = ""
    IDC_PATH = ""

    SERVICES_PATH = ""
    SERVICES_CHILD = ["kill", "login", "sconf", "hips", "echo", "session", "push"]

    PROTOCOL_PATH = ""
    PROTOCOL_CHILD = ["1001", "1200", "7", "100", "1000", "1099", "1100", "1101"]

    GATEWAY_PATH = ""

    TIMEOUT = 3000

    def __init__(self, zk_host, idc_name):
        try:
            self.zk = ZKClient(zk_host, timeout = self.TIMEOUT)
        except ZKClientError, e:
            print("zookeeper init error: %s" % e)
            sys.exit(1)
            return
        except Exception, e:
            print("zookeeper init error: %s, please check you zookeeper host format, example: \"localhost:2181\"" % e)
            sys.exit(1)
            return
        except:
            print("zookeeper init error: unknown error")
            sys.exit(1)
            return

        print("login ok!")

        self.IDC_NAME = idc_name

        # init
        self.InitIdc()

        self.CreateIdcNode()
        self.CreateServiceNodes()
        self.CreateGatewayNode()
        self.CreateProtocolsNodes()

    def InitIdc(self):
        #h  = socket.gethostname();
        #f = h.split('.');
        #if len(f) != 5:
        #    print("invalid hostname format, hostname: %s" % h)
        #    sys.exit(1)
        #idc = f[2]
        print("idc name: %s" % self.IDC_NAME)
        self.IDC_PATH = join(self.ROOT, self.IDC_NAME)
        self.SERVICES_PATH = join(self.IDC_PATH, "services")
        self.PROTOCOL_PATH = join(self.IDC_PATH, "protocols")
        self.GATEWAY_PATH = join(self.IDC_PATH, "gateway")

    def CreateIdcNode(self):
        self.CreateNode([self.ROOT, self.IDC_PATH])

    def CreateServiceNodes(self):
        services = [self.SERVICES_PATH]
        for n in self.SERVICES_CHILD:
            services.append(join(self.SERVICES_PATH, n))
        self.CreateNode(services)

    def CreateGatewayNode(self):
        self.CreateNode([self.GATEWAY_PATH])

    def CreateProtocolsNodes(self):
        protocols = [self.PROTOCOL_PATH]
        for n in self.PROTOCOL_CHILD:
            protocols.append(join(self.PROTOCOL_PATH, n))
        self.CreateNode(protocols)

    def CreateNode(self, nodes):
        for node in nodes: 
            try: 
                if not self.zk.exists(node):
                    print("node %s is not exists and create it" % node)
                    try:
                        self.zk.create(node, "")
                    except Exception, e:
                        print("create %s failed, error: %s" % (node, e))
                        sys.exit(1)
                    except:
                        print("create %s failed, unknown exception" % node)
                        sys.exit(1)
                        pass
                else:
                    print("node %s has existed" % node)
            except Exception, e:
                print("call zookeeper exists error: %s" % e)
                return
            except:
                print("call zookeeper exists error: unknown error")
                pass

def main():
    if len(sys.argv) != 3:
        print("Usage: %s zookeeper_host idc_name" % sys.argv[0])
        print("Example: %s localhost:2181 crop" % sys.argv[0])
        sys.exit(1)
    lcs_zookeeper = LcsZookeeper(sys.argv[1], sys.argv[2])

if __name__ == "__main__":
    main()
