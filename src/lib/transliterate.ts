import Module from "$lib/transliterator.mjs";

const module = await Module();

const orthographies = ["Eatough", "IPA", "Osge"];

export const registerTransliterators = async () =>
  Promise.all(
    orthographies.map((name) =>
      fetch(`/transliterators/${name}_InterNisenan.txt`)
        .then((response) => response.text())
        .then((rules) => module.registerTransliterator(`${name}-InterNisenan`, `InterNisenan-${name}`, rules))
    )
  );

export const transliterate = (
  from: string,
  to: string,
  text: string
): string => {
  const id = `NFD; ${from}-${to}; NFC`;
  return module.transliterate(text, id);
};

export const transliterateFromRules = (text: string, rules: string): string => module.transliterateFromRules(text, rules);

export const toLower = (string: string): string => module.toLower(string);
export const toUpper = (string: string): string => module.toUpper(string);
export const toTitle = (string: string): string => module.toTitle(string);
