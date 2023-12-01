import timeit
import numpy as np
from rivector.wrapper import Vector2Wrapper
import matplotlib.pyplot as plt
from colorama import Fore, Back, Style
import pandas as pd

setup_code = """
import numpy as np
from rivector.wrapper import Vector2Wrapper

vector_a = Vector2Wrapper(10, 10)
vector_b = Vector2Wrapper(20, 20)
vector_c = Vector2Wrapper(30, 30)

array_a = np.array([10, 10])
array_b = np.array([20, 20])
array_c = np.array([30, 30])
"""

vector2wrapper_methods_code = {
    "sqr_magnitude": "vector_a.sqr_magnitude",
    "magnitude": "vector_a.magnitude",
    "normalized": "vector_a.normalized()",
    "dot": "Vector2Wrapper.dot(vector_a, vector_b)",
    "angle": "Vector2Wrapper.angle(vector_a, vector_b)",
    "equals": "Vector2Wrapper.equals(vector_a, vector_b)",
    "clamp_magnitude": "vector_a.clamp_magnitude(3.0)",
    "distance": "vector_a.distance(vector_b)",
    "lerp_unclamped": "vector_a.lerp_unclamped(vector_a, vector_b, 3.0)",
    "max": "Vector2Wrapper.max(vector_a, vector_b)",
    "min": "Vector2Wrapper.min(vector_a, vector_b)",
    "perpendicular": "vector_a.perpendicular(vector_a)",
    "move_towards": "vector_a.move_towards(vector_a, vector_b, 3.0)",
    "reflect": "vector_a.reflect(vector_a, vector_b)",
    "scale": "vector_a.scale(vector_a, 3.0)",
    "signed_angle": "vector_a.signed_angle(vector_b, vector_a)"
}
numpy_methods_code = {
    "sqr_magnitude": "np.sum(array_a ** 2)",
    "magnitude": "np.linalg.norm(array_a)",
    "normalized": "array_a / np.linalg.norm(array_a)",
    "dot": "np.dot(array_a, array_b)",
    "angle": "np.arccos(np.dot(array_a, array_b) / (np.linalg.norm(array_a) * np.linalg.norm(array_b)))",
    "equals": "np.array_equal(array_a, array_b)",
    "clamp_magnitude": "array_a * min(1.0, 3.0 / np.linalg.norm(array_a))",
    "distance": "np.linalg.norm(array_a - array_b)",
    "lerp_unclamped": "array_a + 3.0 * (array_b - array_a)",
    "max": "np.maximum(array_a, array_b)",
    "min": "np.minimum(array_a, array_b)",
    "perpendicular": "np.array([-array_a[1], array_a[0]])",
    "move_towards": "array_a + np.clip(array_b - array_a, -3.0, 3.0)",
    "reflect": "array_a - 2 * np.dot(array_a, array_b) / np.dot(array_b, array_b) * array_b",
    "scale": "array_a * 3.0",
    "signed_angle": "np.sign(np.cross(array_a, array_b)) * np.arccos(np.dot(array_a, array_b) / (np.linalg.norm(array_a) * np.linalg.norm(array_b)))"
}

data_pandas = {
    "method_name": [],
    "numpy": [],
    "vector": []
}

all_numpy = 0
all_vector = 0
for element in numpy_methods_code:
    method_time_vector = timeit.timeit(vector2wrapper_methods_code[element], setup=setup_code, number=10000)
    method_time_numpy = timeit.timeit(numpy_methods_code[element], setup=setup_code, number=10000)
    all_vector += method_time_vector
    all_numpy += method_time_numpy
    
    vector_text = Fore.BLACK+Back.RED+f"Vector2Wrapper {element} Time: {method_time_vector:.6f} seconds"+Style.RESET_ALL
    numpy_text = Fore.BLACK+Back.RED+f"NumPy {element} Time: {method_time_numpy:.6f} seconds"+Style.RESET_ALL
    if method_time_vector < method_time_numpy:
        vector_text = Fore.BLACK+Back.GREEN+f"Vector2Wrapper {element} Time: {method_time_vector:.6f} seconds"+Style.RESET_ALL
    else:
        numpy_text = Fore.BLACK+Back.GREEN+f"NumPy {element} Time: {method_time_numpy:.6f} seconds" +Style.RESET_ALL
    data_pandas["method_name"].append(element)
    data_pandas["numpy"].append(method_time_numpy)
    data_pandas["vector"].append(method_time_vector)
    print(f'{vector_text}\n{numpy_text}\n')

vector_text = Fore.BLACK+Back.RED+f"Vector2Wrapper {all_vector}"+Style.RESET_ALL
numpy_text = Fore.BLACK+Back.RED+f"NumPy {all_numpy}"+Style.RESET_ALL
if all_vector < all_numpy:
    vector_text = Fore.BLACK+Back.GREEN+f"Vector2Wrapper {all_vector}"+Style.RESET_ALL
else:
    numpy_text = Fore.BLACK+Back.GREEN+f"NumPy {all_numpy}" +Style.RESET_ALL
print(f'{vector_text}\n{numpy_text}\n')

df = pd.DataFrame(data_pandas)
print(df.head())
df.to_csv('docs/src/output.csv', index=False)

data_pandas["numpy"] = 1 / np.array(data_pandas["numpy"])
data_pandas["vector"] = 1 / np.array(data_pandas["vector"])

fig, ax = plt.subplots()
bar_width = 0.37

index = np.arange(len(data_pandas["method_name"]))

bar1 = ax.bar(index, data_pandas["numpy"], bar_width, label="numpy")
bar2 = ax.bar(index + bar_width, data_pandas["vector"], bar_width, label="vector")

ax.set_xlabel('Method')
ax.set_ylabel('Productivity (Higher is Better)')
ax.set_title('Comparison of numpy and vector for each method')
ax.set_xticks(index + bar_width / 2)
ax.set_xticklabels(data_pandas["method_name"], fontsize=8)
ax.legend()

plt.show()
