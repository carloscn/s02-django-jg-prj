# -*- coding: utf-8 -*-

from server import server as agent


if __name__ == '__main__':
    agent.init_network(agent)
    agent.run_server(agent)