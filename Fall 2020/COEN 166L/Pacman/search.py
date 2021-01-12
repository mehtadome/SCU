# search.py
# ---------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


"""
In search.py, you will implement generic search algorithms which are called by
Pacman agents (in searchAgents.py).
"""

import util
import sys
import copy
import colored_traceback
colored_traceback.add_hook()


class SearchProblem:
    """
    This class outlines the structure of a search problem, but doesn't implement
    any of the methods (in object-oriented terminology: an abstract class).

    You do not need to change anything in this class, ever.
    """

    def getStartState(self):
        """
        Returns the start state for the search problem.
        """
        util.raiseNotDefined()

    def goalTest(self, state):
        """
          state: Search state

        Returns True if and only if the state is a valid goal state.
        """
        util.raiseNotDefined()

    def getActions(self, state):
        """
        Given a state, returns available actions.
        Returns a list of actions
        """        
        util.raiseNotDefined()

    def getResult(self, state, action):
        """
        Given a state and an action, returns resulting state.
        """
        util.raiseNotDefined()

    def getCost(self, state, action):
        """
        Given a state and an action, returns step cost, which is the incremental cost 
        of moving to that successor.
        """
        util.raiseNotDefined()

    def getCostOfActions(self, actions):
        """
         actions: A list of actions to take

        This method returns the total cost of a particular sequence of actions.
        The sequence must be composed of legal moves.
        """
        util.raiseNotDefined()

class Node:
    """
    Search node object for your convenience.

    This object uses the state of the node to compare equality and for its hash function,
    so you can use it in things like sets and priority queues if you want those structures
    to use the state for comparison.

    Example usage:
    >>> S = Node("Start", None, None, 0)
    >>> A1 = Node("A", S, "Up", 4)
    >>> B1 = Node("B", S, "Down", 3)
    >>> B2 = Node("B", A1, "Left", 6)
    >>> B1 == B2
    True
    >>> A1 == B2
    False
    >>> node_list1 = [B1, B2]
    >>> B1 in node_list1
    True
    >>> A1 in node_list1
    False
    """
    def __init__(self, state, parent, action, path_cost):
        self.state = state
        self.parent = parent
        self.action = action
        self.path_cost = path_cost

    def __hash__(self):
        return hash(self.state)

    def __eq__(self, other):
        return self.state == other.state

    def __ne__(self, other):
        return self.state != other.state


def tinyMazeSearch(problem):
    """
    Returns a sequence of moves that solves tinyMaze.  For any other maze, the
    sequence of moves will be incorrect, so only use this for tinyMaze.
    """
    from game import Directions
    s = Directions.SOUTH
    w = Directions.WEST
    return  [s, s, w, s, w, w, s, w]

def breadthFirstSearch(problem):
    """
    Search the shallowest nodes in the search tree first.

    You are not required to implement this, but you may find it useful for Q5.
    """
    "*** YOUR CODE HERE ***"
    frontier = util.Queue()

    explored = []

    start = problem.getStartState()
    startNode = (start, [], 0)

    frontier.push(startNode)

    while not frontier.isEmpty():
        current_state, actions, current_cost = frontier.pop()

        if current_state not in explored:
            explored.append(current_state)
            
            # if we are at the goal, return list of actions for pacman to take
            if problem.goalTest(current_state):
                return actions
            else:
                for i in problem.getActions(current_state):
                    # find the next action to take
                    new_actions = actions + [i]

                    # find cost given available actions
                    new_cost = current_cost + problem.getCostOfActions(new_actions)

                    # get the next state given the current state and action retrieved
                    new_state = problem.getResult(current_state, i)

                    # new node is the next state found per the next action and total cost
                    newNode = (new_state, new_actions, new_cost)

                    # push the new node to the frontier Queue
                    frontier.push(newNode)
    
    return actions
    
def depthFirstSearch(problem): 

    "*** YOUR CODE HERE ***"  
    frontier = util.Stack()
    explored = []
    
    start = problem.getStartState()
    rootNode = (start, [])  # (state, list of actions)

    frontier.push(rootNode)

    while (not frontier.isEmpty()):
        # current = start, actionList = []
        current_state, actions = frontier.pop()

        if (current_state not in explored):
            # add current state to explored list
            explored.append(current_state)

            # if we are at the goal, return list of actions for pacman to take
            if (problem.goalTest(current_state)):
                return actions
            else:
     
                # loop for recovering each possible actions
                for i in problem.getActions(current_state):
                    # find the next action to take
                    new_actions = actions + [i]

                    # get the next state given the current state and action retrieved
                    new_state = problem.getResult(current_state, i)
                    
                    # new node is the next state found per the next action
                    newNode = (new_state, new_actions)

                    # push the new node to the frontier
                    frontier.push(newNode)
                
    return actions

#getSuccessors() returns successor (which is the next state), action, stepCost
#getResult() returns state      || succState
#getActions() returns actions list    || succAction    
#getCost() returns cost         || succCost

#goalTest() is same as isGoalState()

def nullHeuristic(state, problem=None):
    """
    A heuristic function estimates the cost from the current state to the nearest
    goal in the provided SearchProblem.  This heuristic is trivial.
    """
    return 0

def aStarSearch(problem, heuristic=nullHeuristic):
    """Search the node that has the lowest combined cost and heuristic first."""
    frontier = util.PriorityQueue()

    explored = []

    startState = problem.getStartState()
    start = (startState, [], 0)

    frontier.push(start, 0)

    while (not frontier.isEmpty()):
        # cost + heauristic 
        current_state, actions, current_cost = frontier.pop()

        # put popped node into explored list
        current_node = (current_state, current_cost)

        # put explored node into explored list
        current_node = (current_state, current_cost)

        explored.append((current_state, current_cost))

        # check if reached goal
        if (problem.goalTest(current_state)):
            return actions
        else:
            # loop for recovering each possible actions
            for i in problem.getActions(current_state):
                # find the next action to take
                new_actions = actions + [i]

                # find cost given available actions
                new_cost = current_cost + problem.getCostOfActions(new_actions)

                # get the next state given the current state and action retrieved
                new_state = problem.getResult(current_state, i)

                # new node is the next state found per the next action and total cost
                newNode = (new_state, new_actions, new_cost)

                # check if this node has already been explored
                already_found = False
                for i in explored:
                    explored_state, explored_cost = i
                    # if the state has been explored as well as cost being >= than explored, skip
                    if (new_state == explored_state and new_cost >= explored_cost):
                        already_found = True
                # if current node hasn't been explored, push to frontier and mark as explored
                if (not already_found):
                    # push to frontier
                    frontier.push(newNode, new_cost + heuristic(new_state, problem))
                    # update explored list
                    explored.append((current_state, new_cost))

    return actions

def iterativeDeepeningSearch(problem):
    """
    Perform DFS with increasingly larger depth. Begin with a depth of 1 and increment depth by 1 at every step.

    Your search algorithm needs to return a list of actions that reaches the
    goal. Make sure to implement a graph search algorithm.

    To get started, you might want to try some of these simple commands to
    understand the search problem that is being passed in:

    print("Start:", problem.getStartState())
    print("Is the start a goal?", problem.goalTest(problem.getStartState()))
    print("Actions from start state:", problem.getActions(problem.getStartState()))

    Then try to print the resulting state for one of those actions
    by calling problem.getResult(problem.getStartState(), one_of_the_actions)
    or the resulting cost for one of these actions
    by calling problem.getCost(problem.getStartState(), one_of_the_actions)

    """
    "*** YOUR CODE HERE ***"
    util.raiseNotDefined()
    
def UniformCostSearch(problem):
    """Search the node that has the lowest path cost first."""
    "*** YOUR CODE HERE ***"  
    util.raiseNotDefined()


# Abbreviations
bfs = breadthFirstSearch
astar = aStarSearch
ids = iterativeDeepeningSearch
