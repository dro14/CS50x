#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
bool will_cycle(int winner, int loser);
void lock_pairs(void);
void print_winner(void);



int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}



// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!strcmp(candidates[i], name))
        {
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}


// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    int winner;
    int loser;

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            winner = ranks[i];
            loser = ranks[j];
            preferences[winner][loser]++;
        }
    }
}


// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int winner;
    int loser;

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > 0)
            {
                if (preferences[i][j] > preferences[j][i])
                {
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = j;
                    pair_count++;   // A pair is added to the "pairs" array
                }
                else if (preferences[i][j] < preferences[j][i])
                {
                    pairs[pair_count].winner = j;
                    pairs[pair_count].loser = i;
                    pair_count++;   // A pair is added to the "pairs" array
                }
            }
        }
    }
}


// Sort pairs in decreasing order by strength of victory
// Bubble sort in opposite direcation is used to sort the array
void sort_pairs(void)
{
    int max_strength;   // Pair with maximum victory strength
    pair temp_pair;   // Temporary variable for a pair while swapping pairs
    int winner;
    int loser;

    for (int i = 0; i < pair_count; i++)
    {
        winner = pairs[i].winner;
        loser = pairs[i].loser;

        max_strength = preferences[winner][loser];

        for (int j = i + 1; j < pair_count; j++)
        {
            winner = pairs[j].winner;
            loser = pairs[j].loser;

            if (max_strength < preferences[winner][loser])
            {
                max_strength = preferences[winner][loser];
                temp_pair = pairs[j];
                pairs[j] = pairs[i];
                pairs[i] = temp_pair;
            }
        }
    }
}


// Check whether a given edge creates a cycle
bool will_cycle(int winner, int loser)
{
    if (locked[loser][winner])
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i] && will_cycle(winner, i))
        {
            return true;
        }
    }

    return false;
}


// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    int winner;
    int loser;

    for (int p = 0; p < pair_count; p++)
    {
        winner = pairs[p].winner;
        loser = pairs[p].loser;

        if (!will_cycle(winner, loser))   // Check whether this pair creates a cycle
        {
            locked[winner][loser] = true;
        }
    }
}


// Print the winner of the election
void print_winner(void)
{
    int defeats;   // Number of defeats the current candidate has

    for (int i = 0; i < candidate_count; i++)
    {
        defeats = 0;

        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                defeats++;
            }
        }

        if (defeats == 0)
        {
            printf("%s\n", candidates[i]);
        }
    }
}