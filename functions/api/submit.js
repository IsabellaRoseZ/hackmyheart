// Cloudflare Pages Function: /api/submit
// Stores only hashed flags in the repo (GitHub). The plaintext flag is NOT present.

const FLAG_HASHES = {
  // SHA-256("flag{4}") in hex:
  // (this is just a mock example for the warm-up problem)
  "01": "3b09aeb6f7b9a4d2449c8e2a0d14f6f4c6e3d1b2ef5e74d5f8a0b6f0dfbcb7c7"
};

async function sha256Hex(input) {
  const data = new TextEncoder().encode(input);
  const digest = await crypto.subtle.digest("SHA-256", data);
  return [...new Uint8Array(digest)].map(b => b.toString(16).padStart(2, "0")).join("");
}

export async function onRequestPost({ request }) {
  const form = await request.formData();
  const challenge = String(form.get("challenge") || "");
  const flag = String(form.get("flag") || "");

  if (!FLAG_HASHES[challenge]) {
    return new Response("Invalid challenge.", { status: 400 });
  }

  const submittedHash = await sha256Hex(flag.trim());
  const correctHash = FLAG_HASHES[challenge];

  if (submittedHash === correctHash) {
    return new Response("✅ Correct!", { status: 200 });
  }
  return new Response("❌ Incorrect.", { status: 200 });
}
