export async function onRequestGet({ env }) {
  // Total score per user = sum of challenge values they've solved
  const { results } = await env.DB.prepare(`
    SELECT
      u.username AS username,
      COALESCE(SUM(c.value), 0) AS score
    FROM users u
    LEFT JOIN solves s ON s.user_id = u.id
    LEFT JOIN challenges c ON c.id = s.challenge_id
    GROUP BY u.id
    ORDER BY score DESC, u.username ASC
  `).all();

  return new Response(JSON.stringify({ scoreboard: results }), {
    headers: { "Content-Type": "application/json" }
  });
}
