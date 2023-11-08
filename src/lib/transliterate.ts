import Module from "$lib/transliterator.mjs";
import hash from "object-hash";
const module = await Module();

const orthographies = ["Eatough", "IPA", "Osge"];

export const registerTransliterators = async () =>
  Promise.all(
    orthographies.map((name) =>
      fetch(`/transliterators/${name}_InterNisenan.txt`)
        .then((response) => response.text())
        .then((rules) =>
          module.registerTransliterator(
            `${name}-InterNisenan`,
            `InterNisenan-${name}`,
            rules
          )
        )
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

let transliteratorCache: Set<string> = new Set();

export const transliterateFromRules = (text: string, rules: string): string => {
  const rulesHash = "n" + hash(rules);
  // console.log(hash(rules, { encoding: "buffer" }));
  // const rulesHash = "a123bcdef";
  if (transliteratorCache.has(rulesHash)) {
    // console.log("From Cache: ", rulesHash);
    return module.transliterate(text, rulesHash);
  } else {
    // console.log("Adding to Cache: ", rulesHash);
    transliteratorCache.add(rulesHash);
    return module.transliterateFromRules(text, rules, rulesHash);
  }
};

export const toLower = (string: string): string => module.toLower(string);
export const toUpper = (string: string): string => module.toUpper(string);
export const toTitle = (string: string): string => module.toTitle(string);
