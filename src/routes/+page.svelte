<script lang="ts">
  import { onMount } from "svelte";

  import { slide } from "svelte/transition";

  const baseWords: string[] = [
    "Nišenaan",
    "bysepʼyykʼ",
    "cëëwmukum",
    "homaa haʼukadi",
    `"Nik myymaadi de sawisma!" 
  "Otanbodi de sawisma!"
  "Nik myymaadi de sawisma!"
  "Otanbodi de sawisma!"`,
    `Hace haj mynem pʼusso bycipʼice mym lajim peenim pʼusso moomaam kani kʼaatowineen amam oko mym lajim peenim yneemukum.`,
    `Kʼutʼim pitcaakʼam ham lajim peenim haj ukʼojmukum jamanna pittaatakʼa pakʼoji. Han haj kʼutʼim pitcaakʼam ba toojeen myji pamukum. Hace haj kʼutʼim pitcaakʼak ba cëëwmukum. Hace haj pitcaakʼam woomukum. Han haj woon ekʼojusan emukum sa tajim kʼawna. Han haj 
  "Nik myymaadi de sawisma!" 
  "Otanbodi de sawisma!"
  "Nik myymaadi de sawisma!"
  "Otanbodi de sawisma!"
  Hace haj "Hode? Hode?" hamukum. "Hode mym sam?" "Myym da hodo taji sa." Kʼutʼim myjna etan emukum sa. Han haj kaanteem wakʼa heetʼamukum. Hace haj kaanteem wakʼam ukʼojsyn kʼaamukum sa meekʼojsyn. Han haj kapam hadykym kʼutonim nek kyymukum. Hace haj lismo s woojokʼojmukum. Hace haj lisnom ukʼojin mym sa loomukum. Han haj toojeemukum. Han haj dappe emukum. Hace haj dappem "homaa be, ty?" han "Aj, nikʼi paanim my!" hamukum. "Maatʼim!" hamukum. "Oo, mej nik, ty!" "Pa macakʼii ni!" "Okʼom dani!" "Oo, nikʼi pajjom hesupajim my!" "Oo, mej nik, ty!" "Myji dani aanikʼi!" Hace haj "Oo, sam my!" "Oo, mej nik, ty!" "Mym sa dani aanikʼi!" Han haj... umm... he got mad... Han haj mym sani woʼopajmukum. Hace haj hedem kʼawim samukum. Dappem tʼaanon woonomukum`,
  ];

  let customText = "Nisenaan";

  const orthographyOptions: { [key: string]: { [key: string]: string } } = {
    pʼ: {
      pʼ: "\uE001 > pʼ;",
      ṕ: "\uE001 > ṕ;",
      ᵽ: "\uE001 > ᵽ;",
      ƥ: "\uE001 > ƥ;",
      ṗ: "\uE001 > ṗ;",
      p̣: "\uE001 > p̣;",
    },
    tʼ: {
      tʼ: "\uE004 > tʼ;",
      t́: "\uE004 > t́;",
      ŧ: "\uE004 > ŧ;",
      ƭ: "\uE004 > ƭ;",
      ṭ: "\uE004 > ṭ;",
      ṫ: "\uE004 > ṫ;",
      ʇ: "\uE004 > ʇ;",
    },
    kʼ: {
      kʼ: "\uE00D > kʼ;",
      ḱ: "\uE00D > ḱ;",
      ꝁ: "\uE00D > ꝁ;",
      ƙ: "\uE00D > ƙ;",
      ḳ: "\uE00D > ḳ;",
      k̇: "\uE00D > k̇;",
      ʞ: "\uE00D > ʞ;",
    },
    c: {
      c: "\uE009 > c;",
      ts: "\uE009 > ts;",
      cʼ: "\uE009 > cʼ;",
      ć: "\uE009 > ć;",
      ꞓ: "\uE009 > ꞓ;",
      ƈ: "\uE009 > ƈ;",
      c̣: "\uE009 > c̣;",
      ċ: "\uE009 > ċ;",
      tsʼ: "\uE009 > tsʼ;",
    },
    // Eatough doesn't have a ‹cʼ›, so removing this option until we need it
    // cʼ: {
    //   cʼ: "\uE00A > cʼ;",
    //   ć: "\uE00A > ć;",
    //   ꞓ: "\uE00A > ꞓ;",
    //   ƈ: "\uE00A > ƈ;",
    //   c̣: "\uE00A > c̣;",
    //   tsʼ: "\uE00A > tsʼ;",
    // },
    y: {
      y: "\uE016 > y;",
      ʉ: "\uE016 > ʉ;",
      ɨ: "\uE016 > ɨ;",
    },
    b: {
      b: "\uE01F > b;",
      ƀ: "\uE01F > ƀ;",
      ɓ: "\uE01F > ɓ;",
    },
    d: {
      d: "\uE006 > d;",
      đ: "\uE006 > đ;",
      ɗ: "\uE006 > ɗ;",
    },
    j: {
      j: "\uE00B > j;",
      y: "\uE00B > y;",
    },
    ë: {
      ë: "\uE017 > ë;",
      ə: "\uE017 > ə;",
    },
    ʼ: {
      ʼ: "\uE010 > ʼ;",
      ʔ: "\uE010 > ʔ;",
      ɂ: "\uE010 > ɂ;",
      ˀ: "\uE010 > ˀ;",
      "7": "\uE010 > 7;",
    },
    aa: {
      aa: "\uE018 > \uE011\uE011; \uE019 > \uE012\uE012; \uE01A > \uE013\uE013; \uE01B > \uE014\uE014; \uE01C > \uE015\uE015; \uE01D > \uE016\uE016; \uE01E > \uE017\uE017;",
      aː: "\uE018 > \uE011ː; \uE019 > \uE012ː; \uE01A > \uE013ː; \uE01B > \uE014ː; \uE01C > \uE015ː; \uE01D > \uE016ː; \uE01E > \uE017ː;",
      "a·": "\uE018 > \uE011·; \uE019 > \uE012·; \uE01A > \uE013·; \uE01B > \uE014·; \uE01C > \uE015·; \uE01D > \uE016·; \uE01E > \uE017·;",
      ā: "\uE018 > \uE011\u0304; \uE019 > \uE012\u0304; \uE01A > \uE013\u0304; \uE01B > \uE014\u0304; \uE01C > \uE015\u0304; \uE01D > \uE016\u0304; \uE01E > \uE017\u0304;",
    },
    š: {
      š: "\uE008 > š;",
      sh: "\uE008 > sh;",
      ś: "\uE008 > ś;",
      ş: "\uE008 > ş;",
      ŝ: "\uE008 > ŝ;",
      "ꟊ": "\uE008 > ꟊ;",
      ꞩ: "\uE008 > ꞩ;",
    },
    // č: {
    //   č: "\uE020 > č;",
    //   ch: "\uE020 > ch;",
    //   ç: "\uE020 > ç;",
    //   ĉ: "\uE020 > ĉ;",
    //   ȼ: "\uE020 > ȼ;",
    // },
    // čʼ: {
    //   čʼ: "\uE021 > čʼ;",
    //   chʼ: "\uE021 > chʼ;",
    //   ꞓ̌: "\uE021 > ꞓ̌;",
    //   ƈ̌: "\uE021 > ƈ̌;",
    //   č̣: "\uE021 > č̣;",
    // },
    aj: {
      aj: "",
      ai: "[\uE011-\uE01E] { \uE00B } [^\uE011-\uE01E] > i;",
    },
    p: {
      p: "\uE000 > p;",
    },
    m: {
      m: "\uE002 > m;",
    },
    t: {
      t: "\uE003 > t;",
    },
    n: {
      n: "\uE005 > n;",
    },
    s: {
      s: "\uE007 > s;",
    },
    k: {
      k: "\uE00C > k;",
    },
    w: {
      w: "\uE00E > w;",
    },
    h: {
      h: "\uE00F > h;",
    },
    a: {
      a: "\uE011 > a;",
    },
    e: {
      e: "\uE012 > e;",
    },
    i: {
      i: "\uE013 > i;",
    },
    o: {
      o: "\uE014 > o;",
    },
    u: {
      u: "\uE015 > u;",
    },
  };

  const keyOrder = [
    "aa",
    "aj",
    "ʼ",
    "pʼ",
    "tʼ",
    "kʼ",
    "c",
    // "cʼ",
    // "č",
    // "čʼ",
    "b",
    "d",
    "š",
    "j",
    "ë",
    "y",
    "p",
    "m",
    "t",
    "n",
    "s",
    "k",
    "w",
    "h",
    "a",
    "e",
    "i",
    "o",
    "u",
  ];

  const keyDiff = keyOrder.filter(
    (x) => !Object.keys(orthographyOptions).includes(x)
  );
  const keyDiff2 = Object.keys(orthographyOptions).filter(
    (x) => !keyOrder.includes(x)
  );
  console.assert(
    keyDiff2.length === 0 && keyDiff.length === 0,
    keyDiff,
    keyDiff2
  );

  const complexKeys = ["pʼ", "tʼ", "kʼ", "cʼ", "š", "ë", "ʼ"];

  const fonts = [
    // "Wazhazhe",
    // "Noto Sans Osage",
    "Noto Sans",
    "Noto Serif",
    "Noto Sans Display",
    "Noto Serif Display",
    "Arial",
    "Times New Roman",
    "Cardo",
    "Montserrat",
    "PP Monument Extended",
  ];

  const fontDefaults = {
    size: 12,
    weight: 400,
    width: 100,
    contrast: 0,
    italic: false,
    underline: false,
    smallCaps: false,
  };
  let fontSize: number;
  let fontWeight: number;
  let fontWidth: number;
  let fontContrast: number;
  let fontItalic: boolean;
  let fontUnderline: boolean;
  let fontSmallCaps: boolean;
  let allCaps = false;

  const resetFontOptions = () => {
    fontSize = fontDefaults.size;
    fontWeight = fontDefaults.weight;
    fontWidth = fontDefaults.width;
    fontContrast = fontDefaults.contrast;
    fontItalic = fontDefaults.italic;
    fontUnderline = fontDefaults.underline;
    fontSmallCaps = fontDefaults.smallCaps;
  };
  resetFontOptions();
  let currentOrthography: { [key: string]: string } = keyOrder.reduce(
    (acc, key) => ({ [key]: key, ...acc }),
    {}
  );

  const buildRules = (currentOrthography: { [key: string]: string }) => {
    let rules = "::NFD;";
    keyOrder.forEach((key) => {
      rules += orthographyOptions[key][currentOrthography[key]];
      if (key === "aa" || key === "aj") rules += "::Null;";
    });
    rules += "::NFC;";
    return rules;
  };

  let result: string[] = [];

  let menusOpen: string[] = [];

  const toggleMenu = (option: string) => {
    menusOpen = menusOpen.includes(option) ? [] : [option];
  };

  let shiftPressed = false;

  $: {
    const rules = buildRules(currentOrthography);
    if (transliteratorsRegistered)
      result = [customText, ...baseWords]
        .map((text) =>
          transliterateFromRules(
            transliterate("Eatough", "InterNisenan", text),
            rules
          )
        )
        .map((text) => (allCaps ? text.toUpperCase() : text));
  }

  let transliterate = (from: string, to: string, text: string) => "";
  let transliterateFromRules = (text: string, rules: string) => "";
  let registerTransliterators: () => Promise<any[]>;
  let transliteratorsRegistered = false;
  onMount(async () => {
    ({ transliterate, transliterateFromRules, registerTransliterators } =
      await import("$lib/transliterate"));
    registerTransliterators().then(() => (transliteratorsRegistered = true));
  });
</script>

<svelte:window
  on:keydown={(e) => {
    if (e.key === "Shift") shiftPressed = true;
  }}
  on:keyup={(e) => {
    if (e.key === "Shift") shiftPressed = false;
  }}
/>

<main>
  <div id="options-bar">
    <div id="options-buttons">
      <button on:click={() => toggleMenu("orthography")}>
        Orthography Options
      </button>
      <button on:click={() => toggleMenu("customText")}> Custom Text </button>
      <button on:click={() => toggleMenu("font")}> Font Options </button>
    </div>
    {#if menusOpen.includes("orthography")}
      <div transition:slide class="options">
        {#each keyOrder as inputKey}
          {#if Object.keys(orthographyOptions[inputKey]).length > 1}
            <form class="orthography-option">
              {#each Object.keys(orthographyOptions[inputKey]) as outputKey}
                <input
                  type="radio"
                  bind:group={currentOrthography[inputKey]}
                  name={inputKey}
                  id={inputKey + "-" + outputKey}
                  value={outputKey}
                />
                <label for={inputKey + "-" + outputKey}>{outputKey}</label>
              {/each}
            </form>
          {/if}
        {/each}
      </div>
    {/if}
    {#if menusOpen.includes("customText")}
      <div transition:slide id="custom-text">
        <textarea id="custom-text-area" bind:value={customText} />
        <div>
          {#each complexKeys as key}
            <button
              on:click={() => {
                customText =
                  customText + (shiftPressed ? key.toUpperCase() : key);
                document.getElementById("custom-text-area")?.focus();
              }}
            >
              {shiftPressed ? key.toUpperCase() : key}
            </button>
          {/each}
        </div>
      </div>
    {/if}
    {#if menusOpen.includes("font")}
      <div transition:slide class="options" id="font-options">
        <form class="font-options">
          <label>
            Font Size: {fontSize}
            <input type="range" bind:value={fontSize} />
          </label>
          <label>
            Font Weight: {fontWeight}
            <input type="range" bind:value={fontWeight} min="100" max="900" />
          </label>
          <label>
            Font Width: {fontWidth}
            <input
              type="range"
              bind:value={fontWidth}
              min="62.5"
              max="100"
              step="0.5"
            />
          </label>
          <label>
            Font Contrast: {fontContrast}
            <input type="range" bind:value={fontContrast} min="0" max="100" />
          </label>
          <label style="flex-direction: row;">
            <input type="checkbox" bind:checked={fontItalic} />
            Italic
          </label>
          <label style="flex-direction: row;">
            <input type="checkbox" bind:checked={fontUnderline} />
            Underline
          </label>
          <label style="flex-direction: row;">
            <input type="checkbox" bind:checked={fontSmallCaps} />
            Small Caps
          </label>
          <label style="flex-direction: row;">
            <input type="checkbox" bind:checked={allCaps} />
            All Caps
          </label>
        </form>
        <button on:click={resetFontOptions}>Reset</button>
      </div>
    {/if}
  </div>
  <!-- svelte-ignore a11y-no-static-element-interactions -->
  <!-- svelte-ignore a11y-click-events-have-key-events -->
  <div id="output" on:click={() => (menusOpen = [])}>
    {#each fonts as font}
      <details class="results" style:font-family="'{font}', 'Last Resort'">
        <summary>{font}</summary>
        <div
          style:font-size="{fontSize}pt"
          style:font-variation-settings="'wght' {fontWeight}, 'wdth' {fontWidth},
          'CTGR' {fontContrast}"
          style:font-style={fontItalic ? "italic" : ""}
          style:font-weight={fontWeight}
          style:text-decoration={fontUnderline ? "underline" : ""}
          style:font-variant={fontSmallCaps ? "small-caps" : ""}
        >
          {#each result as output}
            {output}
            <hr />
          {/each}
        </div>
      </details>
    {/each}
  </div>
</main>

<style>
  @import url("https://fonts.cdnfonts.com/css/times-new-roman");
  @import url("https://fonts.cdnfonts.com/css/arial");

  @font-face {
    font-family: "Last Resort";
    src: url("/fonts/LastResort-Regular.ttf") format("truetype");
  }
  @font-face {
    font-family: "Noto Sans";
    src: url("/fonts/NotoSans-VF.ttf") format("truetype-variations");
  }
  @font-face {
    font-family: "Noto Serif";
    src: url("/fonts/NotoSerif-VF.ttf") format("truetype-variations");
  }
  @font-face {
    font-family: "Noto Sans Display";
    src: url("/fonts/NotoSansDisplay-VF.ttf") format("truetype-variations");
  }
  @font-face {
    font-family: "Noto Serif Display";
    src: url("/fonts/NotoSerifDisplay-VF.ttf") format("truetype-variations");
  }
  @font-face {
    font-family: "Noto Sans";
    src: url("/fonts/NotoSans-Italic-VF.ttf") format("truetype-variations");
    font-style: italic;
  }
  @font-face {
    font-family: "Noto Serif";
    src: url("/fonts/NotoSerif-Italic-VF.ttf") format("truetype-variations");
    font-style: italic;
  }
  @font-face {
    font-family: "Noto Sans Display";
    src: url("/fonts/NotoSansDisplay-Italic-VF.ttf")
      format("truetype-variations");
    font-style: italic;
  }
  @font-face {
    font-family: "Noto Serif Display";
    src: url("/fonts/NotoSerifDisplay-Italic-VF.ttf")
      format("truetype-variations");
    font-style: italic;
  }

  @font-face {
    font-family: "Wazhazhe";
    src: url("/fonts/Wazhazhe.ttf") format("truetype");
  }

  @font-face {
    font-family: "Cardo";
    src: url("/fonts/Cardo-Regular.ttf") format("truetype");
  }
  @font-face {
    font-family: "Cardo";
    src: url("/fonts/Cardo-Italic.ttf") format("truetype");
    font-style: italic;
  }

  @font-face {
    font-family: "Cardo";
    src: url("/fonts/Cardo-Bold.ttf") format("truetype");
    font-weight: bold;
  }

  @font-face {
    font-family: "Montserrat";
    src: url("/fonts/Montserrat-VariableFont_wght.ttf")
      format("truetype-variations");
  }
  @font-face {
    font-family: "Montserrat";
    src: url("/fonts/Montserrat-Italic-VariableFont_wght.ttf")
      format("truetype-variations");
    font-style: italic;
  }

  @font-face {
    font-family: "PP Monument Extended";
    src: url("/fonts/PPMonumentExtended-Regular.otf") format("opentype");
  }

  @font-face {
    font-family: "PP Monument Extended";
    src: url("/fonts/PPMonumentExtended-Light.otf") format("truetype");
    font-weight: 300;
  }
  @font-face {
    font-family: "PP Monument Extended";
    src: url("/fonts/PPMonumentExtended-Black.otf") format("truetype");
    font-weight: 900;
  }

  @font-face {
    font-family: "PP Monument Extended";
    src: url("/fonts/PPMonumentExtended-RegularItalic.otf") format("opentype");
    font-style: italic;
  }

  @font-face {
    font-family: "PP Monument Extended";
    src: url("/fonts/PPMonumentExtended-LightItalic.otf") format("truetype");
    font-weight: 300;
    font-style: italic;
  }
  @font-face {
    font-family: "PP Monument Extended";
    src: url("/fonts/PPMonumentExtended-BlackItalic.otf") format("truetype");
    font-weight: 900;
    font-style: italic;
  }

  :root {
    font-family: "Noto Sans";
  }

  main {
    display: flex;
    flex-direction: column;
  }

  #options-bar {
    position: sticky;
    inset-block-start: 8px;
  }
  #options-buttons {
    display: flex;
    flex-direction: row;
    justify-content: space-between;
  }

  .options {
    position: relative;
    background-color: white;
    display: flex;
    flex-direction: column;
    border: 1px black solid;
    padding: 8px;
  }

  #custom-text {
    position: relative;
    display: flex;
    inline-size: auto;
    flex-direction: column;
    align-items: center;
  }

  #custom-text > textarea {
    inline-size: 100%;
  }
  /* #font-options {
      inset-inline-end: 8px;
    } */
  .options > form {
    display: flex;
  }

  .options > form.orthography-option {
    flex-direction: row;
    border-block-end: 1px black solid;
    font-size: 18pt;
  }

  .options > form.font-options {
    flex-direction: column;
  }

  .options > form.font-options > label {
    display: flex;
    flex-direction: column;
  }

  input[type="radio"] {
    appearance: none;
    margin: 0;
    block-size: 0px;
    inline-size: 0px;
  }

  input[type="radio"] + label {
    text-align: center;
    min-inline-size: 24px;
    border-radius: 4pt;
  }
  input[type="radio"]:checked + * {
    background-color: lightblue;
  }
  #output {
    overflow: scroll;
  }
  .results {
    white-space: pre-wrap;
    margin-inline-start: 8px;
    inline-size: fit-content;
  }
</style>
