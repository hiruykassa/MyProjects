import pandas as pd
import plotly.express as px


dCars = pd.read_csv('data/cars.csv')


# Displays
import preswald as p

p.connect()

cars_df = pd.read_csv("data/cars.csv")
cars_df["Horsepower"] = pd.to_numeric(cars_df["Horsepower"], errors="coerce")

p.text("# My Car Data Analysis")
p.table(cars_df, title="Filtered Data")

threshold = p.slider("Threshold", min_val=0, max_val=100, default=50)

filtered = cars_df[cars_df["Horsepower"].notna() & (cars_df["Horsepower"] > threshold)]
p.table(filtered, title="Dynamic Data View")

if all(col in cars_df.columns for col in ["Engine Size (L)", "Year"]):
    fig = px.scatter(data_frame=cars_df, y="Engine Size (L)", x="Year")
    p.plotly(fig)

