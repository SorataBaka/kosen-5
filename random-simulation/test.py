import pandas as pd

def convert_csv(input_path, output_path):
    df = pd.read_csv(input_path)

    def find_correct_letter(row):
        options = [row["Answer1"], row["Answer2"], row["Answer3"], row["Answer4"]]
        correct_answer = row["Correct"]
        try:
            idx = options.index(correct_answer)
            return chr(ord('A') + idx)
        except ValueError:
            # Correct answer not found in options
            return ""

    output_df = pd.DataFrame()
    output_df["QUESTION"] = df["Question"]
    output_df["A"] = df["Answer1"]
    output_df["B"] = df["Answer2"]
    output_df["C"] = df["Answer3"]
    output_df["D"] = df["Answer4"]
    output_df["CORRECT"] = df.apply(find_correct_letter, axis=1)
    output_df["FIXED_ORDER"] = "FALSE"
    output_df["TIME_LIMIT"] = 30

    output_df.to_csv(output_path, index=False)

if __name__ == "__main__":
    convert_csv("input.csv", "output.csv")
