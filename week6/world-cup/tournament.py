# Simulate a sports tournament

import csv
import sys
import random
import math

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    # TODO: Read teams into memory from file
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        for x in reader:
            x["rating"] = int(x["rating"])
            teams.append(x)

    counts = {}
    # TODO: Simulate N tournaments and keep track of win counts
    for _ in range(N):
        winner_name = simulate_tournament(teams)
        if winner_name in counts:
            counts[winner_name] += 1
        else:
            counts[winner_name] = 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""

    num_of_teams = len(teams)
    num_of_rounds = int(math.log(num_of_teams, 2))
    teams_in_round = teams[:]

    for _ in range(num_of_rounds):
        teams_in_round = simulate_round(teams_in_round)

    if len(teams_in_round) == 1:
        return teams_in_round[0]["team"]


if __name__ == "__main__":
    main()