# !/usr/bin/env python
# -*- coding: utf-8 -*-

import numpy as np
import matplotlib.pyplot as plt

def create_example():
	"""
	Creates an example figure.
	"""

	plt.rcParams['figure.figsize'] = (6, 4)

	x = np.array([1, 4, 5, 10])
	y = np.array([1, 7, 5,  8])

	plt.plot(x[::2], y[::2], linestyle='--', color='black')
	plt.plot(x[2:], y[2:], linestyle='--', color='black')
	plt.plot([1, 6], [1, 4.9], linestyle= '--', color='green')
	plt.plot([6, 10], [4.9, 8], linestyle= '--', color='red')
	plt.scatter(x, y, c='black', zorder=99)
	plt.scatter([5, 8], [2, 3], c='black', zorder=99)
	plt.scatter([6], [4.9], c='red', zorder=99)
	plt.title('EDPath Routing Algorithm')

	plt.annotate('optimal endpoint', xy=(6.1, 4.8), xytext=(7.5, 4),
	             arrowprops=dict(facecolor='black', arrowstyle="->",
	             connectionstyle = "arc3"))

	plt.annotate('nearest star', xy=(4.8, 5.1), xytext=(2, 6),
	             arrowprops=dict(facecolor='black', arrowstyle ="->",
	             connectionstyle="arc3"))

	plt.annotate('start', xy=(1, 1.2), xytext=(1, 3),
	             arrowprops=dict(facecolor='black', arrowstyle="->",
	             connectionstyle="arc3"))

	plt.annotate('target', xy=(10, 7.8), xytext=(9, 5),
	             arrowprops=dict(facecolor='black', arrowstyle="->",
	             connectionstyle="arc3"))

	plt.text(4.3, 3.1, 'jump range', color='g')
	plt.axis('off')
	plt.savefig('algorithm.svg')

if __name__ == '__main__':
	create_example()
