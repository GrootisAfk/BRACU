# -*- coding: utf-8 -*-
import random

def pop1(size, N, T):
    pop = []
    count = 0
    while count < size:
        chrm = ''
        i = 0
        while i < N * T:
            chrm += random.choice('01')
            i += 1
        ones = 0
        j = 0
        while j < len(chrm):
            if chrm[j] == '1':
                ones += 1
            j += 1
        if ones > 0:
            pop.append(chrm)
            count += 1
    return pop

def fit1(chrm, N, T):
    ovrlp_pen = 0
    cons_pen = 0
    crs_cnt = [0] * N

    for t in range(T):
        timeslot = chrm[t * N:(t + 1) * N]
        schd_crs = sum(int(timeslot[i]) for i in range(len(timeslot)))
        if schd_crs > 1:
            ovrlp_pen += schd_crs - 1
        for i in range(N):
            if timeslot[i] == '1':
                crs_cnt[i] += 1

    cons_pen += sum(abs(count - 1) for count in crs_cnt)
    tot_pen = ovrlp_pen + cons_pen
    return -tot_pen

def par1(pop, fits):
    tot_fit = sum(fits)
    probs = [fit / tot_fit for fit in fits]
    pars = []
    for _ in range(2):
        r = random.random()
        cum_prob = 0
        for j, prob in enumerate(probs):
            cum_prob += prob
            if r <= cum_prob:
                pars.append(pop[j])
                break
    return pars

def cro1(p1, p2):
    point = random.randint(1, len(p1) - 1)
    offsprng_1 = p1[:point] + p2[point:]
    offsprng_2 = p2[:point] + p1[point:]
    return offsprng_1, offsprng_2

def mut1(chrm, mut_rate):
    mutated = ''.join(
        bit if random.random() > mut_rate else ('1' if bit == '0' else '0')
        for bit in chrm
    )
    return mutated

def gen1(N, T, courses, pop_size, max_gens, mut_rate):
    pop = pop1(pop_size, N, T)
    best_fit = float('-inf')
    best_chrm = None

    for gen in range(max_gens):
        fits = [fit1(chrm, N, T) for chrm in pop]
        for chrm, fit in zip(pop, fits):
            if fit > best_fit:
                best_fit = fit
                best_chrm = chrm

        if best_fit == 0:
            break

        new_pop = []
        while len(new_pop) < pop_size:
            p1, p2 = par1(pop, fits)
            offsprng_1, offsprng_2 = cro1(p1, p2)
            new_pop.append(mut1(offsprng_1, mut_rate))
            if len(new_pop) < pop_size:
                new_pop.append(mut1(offsprng_2, mut_rate))

        pop = new_pop

    return best_chrm, best_fit

def pop2(pop_size, N, T):
    pop = []
    while len(pop) < pop_size:
        chrm = ''.join(random.choice('01') for _ in range(N * T))
        if '1' in chrm:
            pop.append(chrm)
    return pop

def cro2(p1, p2):
    length = len(p1)
    point1 = random.randint(1, length - 2)
    point2 = random.randint(point1 + 1, length - 1)
    offsprng_1 = p1[:point1] + p2[point1:point2] + p1[point2:]
    offsprng_2 = p2[:point1] + p1[point1:point2] + p2[point2:]
    return offsprng_1, offsprng_2

# Main Execution
input_file = "/content/drive/MyDrive/Fall 24/CSE422/Lab_02/Input.txt"

with open(input_file, 'r') as f:
    first_line = f.readline()
    N, T = map(int, first_line.split())
    courses = []
    for _ in range(N):
        course_name = f.readline().strip()
        courses.append(course_name)


# Run the genetic algorithm
best_schedule, best_fitness = gen1(N, T, courses, 100, 1000, 0.01)

print("Best schedule chromosome:", best_schedule)
print("Best fitness:", best_fitness)

# Demonstrate crossover
pop_size = 10
pop = pop2(pop_size, N, T)
p1_idx = random.randint(0, pop_size - 1)
p1 = pop[p1_idx]

p2_idx = p1_idx
while p2_idx == p1_idx:
    p2_idx = random.randint(0, pop_size - 1)
p2 = pop[p2_idx]

offsprng_1, offsprng_2 = cro2(p1, p2)
print("\nParent 1:", p1)
print("Parent 2:", p2)
print("Offspring 1:", offsprng_1)
print("Offspring 2:", offsprng_2)